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

#ifndef CONTENT_H
#define CONTENT_H

#include "../graphics/Image.hpp"
#include "../graphics/ImageLoader.hpp"
#include "../core/ContentManager.hpp"

namespace tigre
{
	namespace kit
	{
		class Content : public core::ContentManager<graphics::Image>
		{
			public:
				
				Content()
				{
					registerLoader(new graphics::ImageLoader(), "jpg,bmp,png");
				}
				
				template<class T>
				T* load(const std::string &filename)
				{
					return ContentManager<T>::load(filename);
				}
				
				template<class T>
				void save(const std::string &filename, const T *resource)
				{
					ContentManager<T>::save(filename, resource);
				}
		};
	}
}

#endif
