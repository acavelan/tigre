#include "android.hpp"

#include "../../core/Exceptions.hpp"

namespace tigre
{
    namespace os
    {
        namespace android
        {
            struct ANativeActivity *gActivity = 0;

            void cacheActivity(struct ANativeActivity *activity)
            {
                gActivity = activity;
            }

            void loadAsset(const std::string &filename, std::string &buffer)
            {
                std::string asset_directory = "file:///android_asset/";
                std::string asset_path = filename.substr(asset_directory.size());

                AAssetManager* assetManager = getAssetManager();
                AAsset* asset = AAssetManager_open(assetManager, (const char *)asset_path.c_str(), AASSET_MODE_UNKNOWN);

                if(asset == NULL)
                    throw core::LoadingFailed(asset_path + ": asset not found\n");

                long size = AAsset_getLength(asset);

                buffer.resize(size);

                AAsset_read(asset, &buffer[0], size);

                AAsset_close(asset);
            }

            struct ANativeActivity *getActivity()
            {
                return gActivity;
            }

            struct AAssetManager* getAssetManager()
            {
                if(gActivity != 0)
                    return gActivity->assetManager;
                else
                    return 0;
            }
        }
    }
}
