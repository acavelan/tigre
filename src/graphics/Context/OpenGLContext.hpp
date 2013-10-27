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

#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include <vector>

#include "config/os.hpp"

#if defined(OS_LINUX)
	#include <GL/gl.h>
	#include <GL/glext.h>
#elif defined(OS_ANDROID)
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#endif

#include "../Display.hpp"
#include "../Context.hpp"
#include "../../utils/Logger.hpp"

namespace tigre
{
	namespace graphics
	{	
		class OpenGLShader
		{
			public:
			
				GLint program;
				GLint ports[shader::count];
		};
		
		class OpenGLContext : public Context
		{
			public:

				OpenGLContext(Display *display);
				~OpenGLContext();
				
				void init();
				void destroy();
				
				void printGLString(GLenum s, const utils::Logger *log);
				void checkGlError(const char* op, const utils::Logger *log);

				void setViewport(int x, int y, int width, int height);
				void setViewport(int width, int height);

				int getX() const;
				int getY() const;

				int getWidth() const;
				int getHeight() const;
				
				void setMatrix4(int port, const glm::mat4 &mat);
				void setColor4(int port, const Color &color);
				
				void setColor(const Color &color);
				
				void clear(const Color &color);
								
				Shader* createShader(ShaderSource *shaderSource);
				void destroy(Shader *shader);
				void setShader(Shader *shader);
				
				OpenGLShader *getCurrentShader();

			private:
			
				GLuint createShader(GLenum shaderType, const char *source);
				GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);

				Display *_display;
				
				OpenGLShader *_currentShader;
				std::vector<OpenGLShader*> _glShaders;
				
				int _x, _y;
				int _width, _height;
				
		};
	}
}

#endif