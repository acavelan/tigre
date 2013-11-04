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

#ifndef CONTEXT_H
#define CONTEXT_H

#include <glm/glm.hpp>

#include "Color.hpp"
#include "Shader.hpp"

/**
 * An OpenGL context represents many things. A context stores all of the state 
 * associated with this instance of OpenGL. It represents the (potentially 
 * visible) default framebuffer that rendering commands will draw to when not 
 * drawing to a framebuffer object. Think of a context as an object that holds 
 * all of OpenGL; when a context is destroyed, OpenGL is destroyed.
 */
namespace tigre
{
	namespace gfx
	{	
		class Context
		{
			public:
				
				virtual ~Context() {}
				
				virtual void init() = 0;
				virtual void destroy() = 0;
				
				virtual void setViewport(int x, int y, int width, int height) = 0;
				virtual void setViewport(int width, int height) = 0;

				virtual int getX() const = 0;
				virtual int getY() const = 0;

				virtual int getWidth() const = 0;
				virtual int getHeight() const = 0;
				
				virtual void setMatrix4(int port, const glm::mat4 &mat) = 0;
				
				virtual void setColor(const Color &color) = 0;
				
				virtual void clear(const Color &color = color::White) = 0;
				
				virtual Shader* createShader(const ShaderSource &shaderSource) = 0;
				virtual void destroy(Shader *shader) = 0;
				
				virtual void setShader(Shader *shader) = 0;
				virtual void setShader(Shader *shader, const Color &color) = 0;
		};
	}
}

#endif
