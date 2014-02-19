#include <jni.h>

#include "core/core.hpp"
#include "gfx/gfx.hpp"
#include "hl/hl.hpp"

#include "core/Logger/AndroidLogger.hpp"
#include "gfx/Display/AndroidDisplay.hpp"
#include "gfx/Context/OpenGLContext.hpp"
#include "gfx/Renderer/OpenGLRenderer.hpp"

#include "Earth.hpp"
#include "EarthActivity.hpp"

using namespace tigre::core;
using namespace tigre::gfx;
using namespace tigre::hl;

/**
 * This is the main entry point of a native application that is using
 * android_native_app_glue.  It runs in its own thread, with its own
 * event loop for receiving input events and doing other things.
 */
void android_main(struct android_app* state)
{
    AndroidLogger logger("Tigre");

    try
    {
        Content content;
        content.addLocation("content", "file:///android_asset");
        content.addLocation("shaders", "file:///android_asset/shaders/100");
        content.registerLoader(new ImageLoader(), "jpg,bmp,png,tga");

        EarthActivity activity(state, &content, &logger);

        Timer timer;
        timer.start();

        while(activity.loop())
        {
            activity.pollEvent();

            if(activity.hasFocus())
                activity.update(timer.tick());
        }
    }
    catch(const Exception &e)
    {
        logger.error(e.what());
    }
}
