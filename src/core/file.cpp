#include <cstdio>

#include "os.hpp"
#include "file.hpp"
#include "Exceptions.hpp"

#if defined(OS_ANDROID)
#include "../core/string.hpp"
#include "../os/android/activity.hpp"
#endif

namespace tigre
{
    namespace core
    {
        void loadFile(const std::string &filename, std::string &buffer)
        {
#if defined(OS_ANDROID)
            std::string asset_direcorty = "file:///android_asset/";

            if(core::startsWith(filename, asset_direcorty))
            {
                std::string asset_path = filename.substr(asset_direcorty.size());
                AAssetManager* assetManager = os::android::getAssetManager();
                AAsset* asset = AAssetManager_open(assetManager, (const char *)asset_path.c_str(), AASSET_MODE_UNKNOWN);

                if(asset == NULL)
                    throw core::LoadingFailed(asset_path + ": lol file not found\n");

                long size = AAsset_getLength(asset);

                buffer.resize(size);

                AAsset_read(asset, &buffer[0], size);

                AAsset_close(asset);

                return;
            }
#endif

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
                throw core::LoadingFailed(filename + ": file not found\n");
        }
    }
}
