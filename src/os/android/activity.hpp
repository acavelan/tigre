#ifndef ACTIVITY_HELPER_H
#define ACTIVITY_HELPER_H

#include <android_native_app_glue.h>

namespace tigre
{
    namespace os
    {
        namespace android
        {
            void cacheActivity(struct ANativeActivity *activity);

            struct ANativeActivity *getActivity();

            struct AAssetManager* getAssetManager();
        }
    }
}

#endif
