#include <string>
#include <string.h>

#include "SOIL.h"
#include "ImageLoader.hpp"
#include "../core/file.hpp"

namespace tigre
{
    namespace gfx
    {
        Image* ImageLoader::loadFromFile(const std::string &filename)
        {
            std::string file;
            core::loadFile(filename, file);

            int channels, width, height;
            unsigned char *data = SOIL_load_image_from_memory
                                  (
                                      (unsigned char*)file.c_str(),
                                      file.size(),
                                      &width, &height, &channels,
                                      SOIL_LOAD_AUTO
                                  );

            if(!data)
            {
                std::string error = std::string(SOIL_last_result()) + "\n";
                throw core::LoadingFailed(filename + ": " + error);
                return 0;
            }
            else
            {
                unsigned char *pixels = new unsigned char[width * height * channels];
                memcpy(pixels, data, width * height * channels * sizeof(unsigned char));
                SOIL_free_image_data(data);

                Image *image = new Image();
                image->width = width;
                image->height = height;
                image->channels = channels;
                image->pixels = pixels;

                return image;
            }
        }
    }
}
