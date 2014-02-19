#ifndef ANDROID_H
#define ANDROID_H

#include <string>

#include <android_native_app_glue.h>

namespace tigre
{
    namespace os
    {
        namespace android
        {
            void cacheActivity(struct ANativeActivity *activity);

            void loadAsset(const std::string &filename, std::string &buffer);

            struct ANativeActivity *getActivity();

            struct AAssetManager* getAssetManager();
        }
    }
}

#endif
