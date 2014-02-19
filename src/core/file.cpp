#include <cstdio>

#include "os.hpp"
#include "file.hpp"
#include "Exceptions.hpp"

#if defined(OS_ANDROID)
#include "../core/string.hpp"
#include "../os/android/android.hpp"
#endif

namespace tigre
{
    namespace core
    {
        void loadFile(const std::string &filename, std::string &buffer)
        {
#if defined(OS_ANDROID)
            std::string asset_directory = "file:///android_asset/";

            if(startsWith(filename, asset_directory))
                os::android::loadAsset(filename, buffer);
            else
#endif
            {
                FILE *fp = fopen(filename.c_str(), "rb");

                if(fp)
                {
                    fseek(fp, 0, SEEK_END);
                    long fsize = ftell(fp);
                    fseek(fp, 0, SEEK_SET);

                    buffer.resize(fsize + 1);
                    fread(&buffer[0], fsize, 1, fp);
                    buffer[fsize] = 0;

                    fclose(fp);
                }
                else
                    throw LoadingFailed(filename + ": file not found\n");
            }
        }
    }
}
