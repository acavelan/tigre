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

#include "OpenGLContext.hpp"

#include "../../core/Exceptions.hpp"
#include "../../conv/string.hpp"

namespace tigre
{
	namespace graphics
	{
		OpenGLContext::OpenGLContext(Display *display) :
			_display(display), _currentShader(0), _x(0), _y(0), _width(0), _height(0)
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
			
			setViewport(0, 0, _display->getWidth(), _display->getHeight());
		}
		
		void OpenGLContext::destroy()
		{
		}

		void OpenGLContext::printGLString(GLenum s, const utils::Logger *log)
		{
			log->info("%s\n", (const char*)glGetString(s));
		}

		void OpenGLContext::checkGlError(const char* op, const utils::Logger *log)
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

		int OpenGLContext::getX() const
		{
			return _x;
		}

		int OpenGLContext::getY() const
		{
			return _y;
		}

		int OpenGLContext::getWidth() const
		{
			return _width;
		}

		int OpenGLContext::getHeight() const
		{
			return _height;
		}
		
		void OpenGLContext::setMatrix4(int port, const glm::mat4 &mat)
		{
			glUniformMatrix4fv(_currentShader->ports[port], 1, GL_FALSE, &mat[0][0]);
		}
		
		void OpenGLContext::setColor4(int port, const Color &color)
		{
			glUniform4f(_currentShader->ports[port], color.r, color.g, color.b, color.a);
		}
		
		void OpenGLContext::clear(const Color &color)
		{
			glClearColor(color.r, color.g, color.b, color.a);
			glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
		}
		
		GLuint createShader(GLenum shaderType, const char *source)
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
							error += conv::toString((int)shaderType) + "\n" + buf + "\n";
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

		GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader)
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
		
		void OpenGLContext::load(Shader *shader)
		{
			OpenGLShader *glShader = new OpenGLShader();
			shader->shaderId = _glShaders.size();
			_glShaders.push_back(glShader);
			
			GLuint vert = createShader(GL_VERTEX_SHADER, shader->vertexShader.c_str());
			GLuint frag = createShader(GL_FRAGMENT_SHADER, shader->fragmentShader.c_str());
			
			glShader->program = createShaderProgram(vert, frag);
			glShader->ports[shader::projection] = glGetUniformLocation(glShader->program, "projMat");
			glShader->ports[shader::view] = glGetUniformLocation(glShader->program, "viewMat");
			glShader->ports[shader::model] = glGetUniformLocation(glShader->program, "modelMat");
			glShader->ports[shader::color] = glGetUniformLocation(glShader->program, "color");
			glShader->ports[shader::position] = glGetAttribLocation(glShader->program, "position");
			glShader->ports[shader::normal] = glGetAttribLocation(glShader->program, "normal");
			glShader->ports[shader::texCoord] = glGetAttribLocation(glShader->program, "texCoord");
			glShader->ports[shader::texture0] = glGetAttribLocation(glShader->program, "texture0");
		}
				
		void OpenGLContext::unload(Shader *shader)
		{
			if(shader)
			{
				OpenGLShader *glShader = _glShaders[shader->shaderId];
				
				if(glShader->program)
					glDeleteProgram(glShader->program);
				
				delete glShader;
			}
		}
		
		void OpenGLContext::setShader(Shader *shader)
		{
			OpenGLShader *glShader = _glShaders[shader->shaderId];
			
			if(shader)
				_currentShader = glShader;
			else
				_currentShader = 0;

			glUseProgram(_currentShader->program);
		}
		
		OpenGLShader *OpenGLContext::getCurrentShader()
		{
			return _currentShader;
		}
	}
}
