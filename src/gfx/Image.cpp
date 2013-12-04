#include "Image.hpp"

namespace tigre
{
    namespace gfx
    {
        Image::Image() :
            channels(0), width(0), height(0), pixels(0)
        {
        }

        Image::~Image()
        {
            if(pixels) delete[] pixels;
        }
    }
}
