#ifndef LOADER_H
#define LOADER_H

#include <string>

#include "Exceptions.hpp"

namespace tigre
{
    namespace core
    {
        template <class T>
        class Loader
        {
            public:

                virtual ~Loader() {}

                virtual T* loadFromFile(const std::string &filename)
                {
                    throw NotImplementedException("Failed to load " + filename + ": loadFromFile() not implemented for this class\n");
                }

                virtual void saveToFile(const std::string &filename, const T*)
                {
                    throw NotImplementedException("Failed to load " + filename + ": usaveToFile() not implemented for this class\n");
                }
        };
    }
}

#endif
