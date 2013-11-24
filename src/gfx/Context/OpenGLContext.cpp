/*
TIGRE (https://gitorious.org/tigre) is made available under the MIT License.

Copyright (c) 2012 - 2013 Aurélien Cavelan (razlock)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include <cstdlib>
#include <string>

#include <glm/gtc/type_ptr.hpp>

#include "OpenGLContext.hpp"

#include "../../core/Exceptions.hpp"
#include "../../core/string.hpp"

namespace tigre
{
	namespace gfx
	{
		OpenGLContext::OpenGLContext() :
			_shader(0), _x(0), _y(0), _width(0), _height(0)
		{
		}

		OpenGLContext::~OpenGLContext()
		{
			destroy();
		}

		void OpenGLContext::init()
		{
			glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
			glPixelStorei(GL_PACK_ALIGNMENT, 1);
		}
		
		void OpenGLContext::destroy()
		{
		}

		void OpenGLContext::printGLString(GLenum s, const core::Logger *log)
		{
			log->info("%s\n", (const char*)glGetString(s));
		}

		void OpenGLContext::checkGlError(const char* op, const core::Logger *log)
		{
			for(GLint error = glGetError(); error; error = glGetError())
				log->error("%s glError (0x%x)\n", op, error);
		}

		void OpenGLContext::setViewport(int x, int y, int width, int height)
		{
			_x = x;
			_y = y;
			_width = width;
			_height = height;
			glViewport(x, y, _width, _height);
		}

		void OpenGLContext::setViewport(int width, int height)
		{
			setViewport(0, 0, width, height);
		}

		int OpenGLContext::getViewPortX() const
		{
			return _x;
		}

		int OpenGLContext::getViewPortY() const
		{
			return _y;
		}

		int OpenGLContext::getViewPortWidth() const
		{
			return _width;
		}

		int OpenGLContext::getViewPortHeight() const
		{
			return _height;
		}
		
		void OpenGLContext::setMatrix4(int port, const glm::mat4 &mat)
		{
			glUniformMatrix4fv(_shader->ports[port], 1, GL_FALSE, glm::value_ptr(mat));
		}
		
		void OpenGLContext::setFloat4(int port, float a, float b, float c, float d)
		{
			glUniform4f(_shader->ports[port], a, b, c, d);
		}
		
		void OpenGLContext::clear(const Color &color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		}
		
		GLuint OpenGLContext::createShader(GLenum shaderType, const char *source)
		{
			GLuint shader = glCreateShader(shaderType);
			if(shader)
			{
				glShaderSource(shader, 1, &source, NULL);
				glCompileShader(shader);
				GLint compiled = 0;
				glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
				if(!compiled)
				{
					GLint infoLen = 0;
					glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
					if(infoLen)
					{
						std::string error = "Could not compile shader";
						
						char* buf = new char[infoLen];
						if(buf)
						{
							glGetShaderInfoLog(shader, infoLen, NULL, buf);
							error += core::toString((int)shaderType) + "\n" + buf + "\n";
							delete[] buf;
						}
						glDeleteShader(shader);
						shader = 0;
						
						throw core::LoadingFailed(error);
					}
				}
			}
			return shader;
		}

		GLuint OpenGLContext::createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
		{
			GLuint program = glCreateProgram();
			if(program)
			{
				glAttachShader(program, vertexShader);
				//checkGlError("glAttachShader");
				glAttachShader(program, fragmentShader);
				//checkGlError("glAttachShader");
				glLinkProgram(program);
				GLint linkStatus = GL_FALSE;

				glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

				if(linkStatus != GL_TRUE)
				{
					GLint bufLength = 0;
					glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
					
					std::string error = "Could not link program:";
					
					if(bufLength)
					{
						char* buf = new char[bufLength];
						if(buf)
						{
							glGetProgramInfoLog(program, bufLength, NULL, buf);
							error += "\n" + std::string(buf) + "\n";
							delete[] buf;
						}
					}
					glDeleteProgram(program);
					program = 0;
					
					throw core::LoadingFailed(error);
				}
			}
			return program;
		}
		
		Shader* OpenGLContext::createShader(const ShaderSource &shaderSource)
		{
			OpenGLShader *glShader = new OpenGLShader();
			Shader *shader = new Shader();
			
			shader->token = _glShaders.size();
			
			_glShaders.push_back(glShader);
			
			GLuint vert = createShader(GL_VERTEX_SHADER, shaderSource.vertexShader.c_str());
			GLuint frag = createShader(GL_FRAGMENT_SHADER, shaderSource.fragmentShader.c_str());
			
			glShader->program = createShaderProgram(vert, frag);
			glShader->ports[shader::projection] = glGetUniformLocation(glShader->program, "projection");
			glShader->ports[shader::model] = glGetUniformLocation(glShader->program, "model");
			glShader->ports[shader::view] = glGetUniformLocation(glShader->program, "view");
			glShader->ports[shader::color] = glGetUniformLocation(glShader->program, "color");
			glShader->ports[shader::position] = glGetAttribLocation(glShader->program, "position");
			glShader->ports[shader::normal] = glGetAttribLocation(glShader->program, "normal");
			glShader->ports[shader::texCoord] = glGetAttribLocation(glShader->program, "texCoord");
			glShader->ports[shader::texture0] = glGetAttribLocation(glShader->program, "texture0");
			
			return shader;
		}
				
		void OpenGLContext::destroy(Shader *shader)
		{
			if(shader)
			{
				OpenGLShader *glShader = _glShaders[shader->token];
				
				if(glShader->program)
					glDeleteProgram(glShader->program);
				
				delete glShader;
				
				core::release(shader);
			}
		}
		
		void OpenGLContext::setShader(Shader *shader)
		{
			OpenGLShader *glShader = _glShaders[shader->token];
			
			if(shader)
				_shader = glShader;
			else
				_shader = 0;

			glUseProgram(_shader->program);
		}
		
		OpenGLShader *OpenGLContext::getCurrentShader()
		{
			return _shader;
		}
	}
}
