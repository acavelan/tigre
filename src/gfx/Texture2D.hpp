#ifndef TEXTURE2D_H
#define TEXTURE2D_H

#include "../core/Resource.hpp"

namespace tigre
{
    namespace gfx
    {
        class Texture2D : public core::Resource
        {
            public:

                Texture2D();

                virtual ~Texture2D();

                int token;

                int width, height;
        };
    }
}

#endif
