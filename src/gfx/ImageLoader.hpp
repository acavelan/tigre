#ifndef IMAGE_LOADER_H
#define IMAGE_LOADER_H

#include "Image.hpp"
#include "../core/Loader.hpp"

namespace tigre
{
    namespace gfx
    {
        class ImageLoader : public core::Loader<Image>
        {
            public:

                Image* loadFromFile(const std::string &filename);

        };
    }
}

#endif
