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

#ifndef RENDERER_H
#define RENDERER_H

#include "config.h"

#if defined(OS_LINUX)
	#include <GL/gl.h>
	#include <GL/glext.h>
#elif defined(OS_ANDROID)
	#include <GLES2/gl2.h>
	#include <GLES2/gl2ext.h>
#endif

/**
 * Base class for the Renderer
 *
 * The goal of this class is to abstract everything that concerns
 * native 3D API calls.
 *
 * Renderer can be implemented through OpenGL (Linux / Windows), 
 * OpenGL ES 1.1 / 2.0 (phones, tablets), or even DirectX.
 */
 
namespace tigre
{
	namespace graphics
	{
		class Renderer
		{
			public:
				
				virtual ~Renderer() {}
				
				virtual void printGLString(const char *name, GLenum s) = 0;
				virtual void checkGlError(const char* op) = 0;
				
				virtual void setViewport(int x, int y, int width, int height) = 0;
				virtual void setViewport(int width, int height) = 0;

				virtual int getX() const = 0;
				virtual int getY() const = 0;

				virtual int getWidth() const = 0;
				virtual int getHeight() const = 0;

				virtual void swapBuffers() = 0;
				
				virtual GLuint loadShader(GLenum shaderType, const char *pSource) = 0;
				virtual GLuint createProgram(const char *pVertexSource, const char *pFragmentSource) = 0;
			
		};
	}
}

#endif
