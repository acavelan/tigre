#include "activity.hpp"

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
