#ifndef APP_HANDLER_H
#define APP_HANDLER_H

#include <android/sensor.h>

#include "core/Logger.hpp"
#include "gfx/Display/AndroidDisplay.hpp"
#include "gfx/Context/OpenGLContext.hpp"
#include "gfx/Renderer/OpenGLRenderer.hpp"

#include "os/android/Activity.hpp"

#include "Application.hpp"

using namespace tigre::core;
using namespace tigre::game;
using namespace tigre::gfx;
using namespace tigre::os;

class AppHandler : public android::Activity
{
    public:

        AppHandler(	struct android_app *state, Logger *log,
                    AndroidDisplay *display,
                    OpenGLContext *context,
                    OpenGLRenderer *renderer,
                    Application *app);

        ~AppHandler();

        virtual void onInitWindow();

        virtual void onTermWindow();

        virtual void onWindowResized();

        virtual void onConfigChanged();

        virtual void onGainedFocus();

        virtual void onLostFocus();

        virtual void onStart();

        virtual void onResume();

        virtual void onSaveState();

        virtual void onLoadState(void *state);

        virtual void onPause();

        virtual void onStop();

        virtual void onDestroy();

        virtual void onEvent();

        virtual int onInputEvent(AInputEvent* event);

        // App state
        bool hasFocus() const;

        bool loop() const;

        void close();

        // Accelerometer
        void accSetup();
        void accRelease();

    private:

        Logger *_log;
        AndroidDisplay *_display;
        OpenGLContext *_context;
        OpenGLRenderer *_renderer;

        // Application
        Application *_app;

        // State
        bool _hasFocus;
        bool _loop;

        // Accelerometer
        ASensorManager *sensorManager;
        const ASensor *accelerometerSensor;
        ASensorEventQueue *sensorEventQueue;

};

#endif
