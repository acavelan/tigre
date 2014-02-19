#include "Content.hpp"

#include "../core/file.hpp"

namespace tigre
{
    namespace hl
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
