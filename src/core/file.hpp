#ifndef CORE_FILE_H
#define CORE_FILE_H

#include <string>

namespace tigre
{
    namespace core
    {
        void loadFile(const std::string &filename, std::string &buffer);
    }
}

#endif
