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

#include "Texture2D.hpp"

namespace tigre
{
	namespace graphics
	{
		Texture2D::Texture2D(Image *image) : 
			_bound(false), _image(image), _textureId(-1)
		{
			core::resource::grab(image);
		}
		
		Texture2D::~Texture2D()
		{
			core::resource::release(_image);
		}
			
		Image *Texture2D::getImage()
		{
			return _image;
		}
		
		bool Texture2D::isBound() const
		{
			return _bound;
		}
		
		void Texture2D::isBound(bool bound)
		{
			_bound = bound;
		}
		
		int Texture2D::getTextureId() const
		{
			return _textureId;
		}
				
		void Texture2D::setTextureId(int id)
		{
			_textureId = id;
		}
	}
}
