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

#include "Content.hpp"
#include "../core/file.hpp"

namespace tigre
{
	namespace game
	{
		void Content::addLocation(const std::string &name, const std::string &path)
		{
			_locations[name] = path;
		}
		
		void Content::loadFile(const std::string &filename, std::string &buffer)
		{
			std::string prefix = core::getPrefix(filename, ":");
					
			if(!prefix.empty())
			{
				if(_locations.find(prefix) != _locations.end())
				{
					std::string suffix = core::getSuffix(filename, ":");
					std::string path = _locations.at(prefix) + "/" + suffix;
					core::loadFile(path, buffer);
				}
				else
					throw core::LoadingFailed("unknown prefix: " + prefix);
			}
			else
				core::loadFile(filename, buffer);
		}
	}
}
