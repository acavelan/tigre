#ifndef CONTENT_LOADER_H
#define CONTENT_LOADER_H

#include <map>
#include <string>
#include <vector>

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

                T* loadFromFile(const std::string &filename);

                void saveToFile(const std::string &filename, const T *resource);

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
