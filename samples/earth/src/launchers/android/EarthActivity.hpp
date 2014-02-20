#ifndef EARTH_ACTIVITY_H
#define EARTH_ACTIVITY_H

#include <android/sensor.h>

#include "core/Logger.hpp"
#include "gfx/Display/AndroidDisplay.hpp"
#include "gfx/Context/OpenGLContext.hpp"
#include "gfx/Renderer/OpenGLRenderer.hpp"

#include "os/android/Activity.hpp"

#include "Earth.hpp"

using namespace tigre::core;
using namespace tigre::gfx;
using namespace tigre::hl;
using namespace tigre::os;

class EarthActivity : public android::Activity
{
    public:

        EarthActivity(struct android_app *state, Content *content, Logger *logger);

        ~EarthActivity();

        void onInitWindow();

        void onTermWindow();

        void onWindowResized();

        void onConfigChanged();

        void onGainedFocus();

        void onLostFocus();

        void onStart();

        void onResume();

        void onSaveState();

        void onLoadState(void *state);

        void onPause();

        void onStop();

        void onDestroy();

        void onEvent();

        int onInputEvent(AInputEvent* event);

        // App state
        bool hasFocus() const;

        bool loop() const;

        void update(float tick);

        // Accelerometer
        void accSetup();
        void accRelease();

    private:

        Logger *_log;
        Content *_content;
        AndroidDisplay *_display;
        OpenGLContext *_context;
        OpenGLRenderer *_renderer;
        RenderView *_renderView;

        // Application
        Earth *_app;

        // State
        bool _hasFocus;
        bool _loop;

        // Accelerometer
        ASensorManager *sensorManager;
        const ASensor *accelerometerSensor;
        ASensorEventQueue *sensorEventQueue;

};

#endif
