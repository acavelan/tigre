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

#ifndef CONTENT_LOADER_H
#define CONTENT_LOADER_H

#include <map>
#include <string>
#include <vector>

#include "file.hpp"
#include "string.hpp"
#include "Loader.hpp"
#include "Resource.hpp"
#include "Exceptions.hpp"

namespace tigre
{
	namespace core
	{
		template <class T>
		class ContentLoader
		{
			public:

				virtual ~ContentLoader();
				
				T* load(const std::string &filename);
				
				void save(const std::string &filename, const T *resource);
				
				void registerLoader(Loader<T> *loader, const std::string &extensions);
				
				void unregisterLoaders();
				
				Loader<T>* findLoader(const std::string &filename);
				
			protected:
				
				typedef std::map<std::string, Loader<T>*> LoaderMap;
				typedef std::vector<Loader<T>*> LoaderList;
				
				LoaderList _loaderList;
				LoaderMap _loaderMap;
		};
		
		#include "ContentLoader.inl"
	}
}

#endif
