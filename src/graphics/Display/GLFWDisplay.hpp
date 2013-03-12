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

#ifndef GLFW_DISPLAY_H
#define GLFW_DISPLAY_H

#include <GL/glfw.h>
#include "../Display.hpp"

namespace tigre
{
	namespace graphics
	{
		class GLFWDisplay : public Display
		{
			public:

				GLFWDisplay(int width, int height, bool fullscreen = false);
				~GLFWDisplay();

				virtual void initialize();

				virtual bool valid() const;
						
				virtual void resize(int width, int height);
				
				virtual int getWidth() const;
				virtual int getHeight() const;
				
				virtual void swapBuffers();
				
			private:
				
				bool _valid;
				int _width, _height;
				bool _fullscreen;
		};
	}
}

#endif
