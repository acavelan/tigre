#ifndef IMAGE_H
#define IMAGE_H

#include "../core/Resource.hpp"

namespace tigre
{
    namespace gfx
    {
        class Image : public core::Resource
        {
            public:

                Image();

                virtual ~Image();

                int channels;
                int width, height;
                unsigned char *pixels;
        };
    }
}

#endif
