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

#include <string>
#include <string.h>

#include "ImageLoader.hpp"

#include "SOIL.h"

namespace tigre
{
	namespace graphics
	{
		Image *ImageLoader::loadFromFile(const std::string &filename)
		{
			int channels, width, height;
			unsigned char *data = SOIL_load_image
			(
				filename.c_str(),
				&width, &height, &channels,
				SOIL_LOAD_AUTO
			);
			
			if(!data)
			{
				std::string error = SOIL_last_result();
				throw core::LoadingFailed(error);
				return 0;
			}
			else
			{
				unsigned char *pixels = new unsigned char[width * height * channels];
				memcpy(pixels, data, width * height * channels * sizeof(unsigned char));
				SOIL_free_image_data(data);
				
				Image *image = new Image();
				image->width = width;
				image->height = height;
				image->channels = channels;
				image->pixels = pixels;
				
				return image;
			}
		}
	}
}
