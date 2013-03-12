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

#include "OpenGLRenderer.hpp"

OpenGLRenderer::OpenGLRenderer(Display *display) :
    _display(display), _x(0), _y(0), _width(0), _height(0)
{
}

OpenGLRenderer::~OpenGLRenderer()
{
}

void OpenGLRenderer::initialize()
{
	if(!_display->valid())
	{
		//Log::error("Calling OpenGLRenderer::initialize() before initializing the display\n");
		return;
	}
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glPixelStorei(GL_PACK_ALIGNMENT, 1);
}

void OpenGLRenderer::printGLString(const char *name, GLenum s)
{
    const char *v = (const char *) glGetString(s);
    //Log::info("GL %s = %s\n", name, v);
}

void OpenGLRenderer::checkGlError(const char* op)
{
    //for(GLint error = glGetError(); error; error = glGetError())
      //  Log::error("before %s glError (0x%x)\n", op, error);
}

void OpenGLRenderer::setViewport(int x, int y, int width, int height)
{
    _x = x;
    _y = y;
    _width = width;
    _height = height;
    glViewport(x, y, _width, _height);
}

void OpenGLRenderer::setViewport(int width, int height)
{
    _x = 0;
    _y = 0;
    _width = width;
    _height = height;
    glViewport(0, 0, _width, _height);
}

int OpenGLRenderer::getX() const
{
    return _x;
}

int OpenGLRenderer::getY() const
{
    return _y;
}

int OpenGLRenderer::getWidth() const
{
    return _width;
}

int OpenGLRenderer::getHeight() const
{
    return _height;
}

void OpenGLRenderer::swapBuffers()
{
    _display->swapBuffers();
}

GLuint OpenGLRenderer::loadShader(GLenum shaderType, const char *pSource)
{
    GLuint shader = glCreateShader(shaderType);
    if (shader)
    {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled)
        {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen)
            {
                char* buf = (char*) malloc(infoLen);
                if (buf)
                {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    //Log::error("Could not compile shader %d:\n%s\n", shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint OpenGLRenderer::createProgram(const char *pVertexSource, const char *pFragmentSource)
{
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader)
        return 0;

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader)
        return 0;

    GLuint program = glCreateProgram();
    if (program)
    {
        glAttachShader(program, vertexShader);
        //checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        //checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;

        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        if (linkStatus != GL_TRUE)
        {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf)
                {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    //Log::error("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}
