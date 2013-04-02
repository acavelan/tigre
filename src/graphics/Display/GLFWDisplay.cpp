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

#include <GL/glfw.h>

#include "GLFWDisplay.hpp"

namespace tigre
{
	namespace graphics
	{
		GLFWDisplay::GLFWDisplay(int width, int height, bool fullscreen) :
			_valid(false), _width(width), _height(height), _fullscreen(fullscreen)
		{
		}

		GLFWDisplay::~GLFWDisplay()
		{
		}

		void GLFWDisplay::initialize()
		{
			if(_fullscreen && glfwOpenWindow(_width, _height, 5, 6, 5, 0, 8, 0, GLFW_FULLSCREEN))
				_valid = true;
			else if(glfwOpenWindow(_width, _height, 5, 6, 5, 0, 8, 0, GLFW_WINDOW))
				_valid = true;
		}

		bool GLFWDisplay::valid() const
		{
			return _valid;
		}

		void GLFWDisplay::resize(int width, int height)
		{
			_width = width;
			_height = height;
		}

		int GLFWDisplay::getWidth() const
		{
			return _width;
		}

		int GLFWDisplay::getHeight() const
		{
			return _height;
		}

		void GLFWDisplay::swapBuffers()
		{
			glfwSwapBuffers();
		}
	}
}
