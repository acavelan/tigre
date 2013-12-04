#include <jni.h>

#include "core/core.hpp"
#include "game/game.hpp"
#include "gfx/gfx.hpp"

#include "core/Logger/AndroidLogger.hpp"
#include "gfx/Display/AndroidDisplay.hpp"
#include "gfx/Context/OpenGLContext.hpp"
#include "gfx/Renderer/OpenGLRenderer.hpp"

#include "Application.hpp"
#include "AppHandler.hpp"

using namespace tigre::core;
using namespace tigre::game;
using namespace tigre::gfx;

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
        OpenGLContext context;
        AndroidDisplay display;
        OpenGLRenderer renderer(&context);

        Content content;
        content.addLocation("content", "file:///android_asset");
        content.addLocation("shaders", "file:///android_asset/shaders/100");
        content.registerLoader(new ImageLoader(), "jpg,bmp,png,tga");

        Application app(&display, &context, &renderer, &content, &logger);

        AppHandler handler(state, &logger, &display, &context, &renderer, &app);

        Timer timer;
        timer.start();

        while(handler.loop())
        {
            handler.pollEvent();

            if(handler.hasFocus())
            {
                app.update(timer.tick());
                if(display.valid())
                {
                    app.drawFrame();
                    display.swapBuffers();
                    context.checkGlError("drawFrame()", &logger);
                }
            }
        }
    }
    catch(const Exception &e)
    {
        logger.error(e.what());
    }
}
