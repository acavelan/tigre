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

#ifndef CONTENT_MANAGER_H
#define CONTENT_MANAGER_H

#include <map>
#include <string>
#include <vector>

#include "Loader.hpp"
#include "Resource.hpp"
#include "Exceptions.hpp"

#include "../conv/string.hpp"

namespace tigre
{
	namespace core
	{
		template <class T>
		class ContentManager
		{
			public:

				virtual ~ContentManager()
				{
					unregisterLoaders();
				}
				
				virtual T* load(const std::string &filename)
				{
					Loader<T> *loader = findLoader(filename);
					T *resource = loader->loadFromFile(filename);
					return resource;
				}
				
				virtual void unload(T *resource)
				{
					resource::release(resource);
				}
				
				virtual void save(const std::string &filename, const T *resource)
				{
					Loader<T> *loader = findLoader(filename);
					loader->saveToFile(filename, resource);
				}
				
				void registerLoader(Loader<T> *loader, const std::string &extensions)
				{
					std::vector<std::string> extList;
					conv::split(extensions, extList, " /\\*.,;|-_\t\n'\"");

					std::vector<std::string>::iterator it, end = extList.end();
					for(it = extList.begin(); it != end; ++it)
						_loaderMap[conv::toLower(*it)] = loader;
					
					_loaderList.push_back(loader);
				}
				
				void unregisterLoaders()
				{
					typename LoaderList::iterator it, end = _loaderList.end();
					for(it = _loaderList.begin(); it != end; it++)
					{
						delete *it;
					}
					_loaderList.clear();
				}
				
				Loader<T>* findLoader(const std::string &filename)
				{
					std::string extension = conv::toLower(getExtension(filename));
					
					typename LoaderMap::iterator it = _loaderMap.find(extension);

					if(it != _loaderMap.end())
						return it->second;
					
					it = _loaderMap.find("*");
					
					bool any = (it != _loaderMap.end());
					
					if(any)
						return it->second;
					else
						throw LoadingFailed("No loaders for this extension: " + extension + "\n");
				
				}
				
				std::string getExtension(const std::string &filename) const
				{
					std::string extension = "";
					bool find = false;
					
					int size = filename.size();
					for(int i=size-1; i>0 && !find; i--)
					{
						if(filename[i] == '.') find = true;
						else extension = filename[i] + extension;
					}
					
					return extension;
				}
				
			protected:
				
				typedef std::map<std::string, Loader<T>*> LoaderMap;
				typedef std::vector<Loader<T>*> LoaderList;
				
				LoaderList _loaderList;
				LoaderMap _loaderMap;
		};
	}
}

#endif
