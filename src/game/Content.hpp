#ifndef CONTENT_H
#define CONTENT_H

#include <map>

#include "core/ContentLoader.hpp"
#include "gfx/Image.hpp"

namespace tigre
{
    namespace game
    {
        class Content : public core::ContentLoader<gfx::Image>
        {
            public:

                void addLocation(const std::string &name, const std::string &path);

                void loadFile(const std::string &filename, std::string &buffer);

                template<class T>
                T* loadFromFile(const std::string &filename)
                {
                    std::string prefix = core::getPrefix(filename, ":");

                    if(!prefix.empty())
                    {
                        if(_locations.find(prefix) != _locations.end())
                        {
                            std::string suffix = core::getSuffix(filename, ":");
                            std::string path = _locations.at(prefix) + "/" + suffix;
                            return ContentLoader<T>::loadFromFile(path);
                        }
                        else
                            throw core::LoadingFailed("unknown prefix: " + prefix);
                    }
                    else
                        return ContentLoader<T>::loadFromFile(filename);
                }

                template<class T>
                void saveToFile(const std::string &filename, const T *resource)
                {
                    ContentLoader<T>::saveToFile(filename, resource);
                }

            private:

                std::map<std::string, std::string> _locations;
        };
    }
}

#endif
