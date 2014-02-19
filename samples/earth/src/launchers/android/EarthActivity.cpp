#include "EarthActivity.hpp"

EarthActivity::EarthActivity(struct android_app *state, Content *content, Logger *logger) :
    Activity(state), _content(content), _log(logger), _display(0), _context(0), _renderer(0), _hasFocus(true), _loop(true)
{
    _log->info("EarthActivity::EarthActivity(state)");

    sensorManager = ASensorManager_getInstance();
    accelerometerSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    sensorEventQueue = ASensorManager_createEventQueue(sensorManager, getState()->looper, LOOPER_ID_USER, NULL, NULL);
}

EarthActivity::~EarthActivity()
{
    _log->info("EarthActivity::~EarthActivity()");
}

void EarthActivity::onInitWindow()
{
    _log->info("EarthActivity::onInitWindow()");

    if(getState()->window != NULL)
    {
        _display = new AndroidDisplay(getState()->window);

        _context = new OpenGLContext();

        _context->printGLString(GL_VENDOR, _log);
        _context->printGLString(GL_RENDERER, _log);
        _context->printGLString(GL_VERSION, _log);
        _context->printGLString(GL_SHADING_LANGUAGE_VERSION, _log);

        _renderer = new OpenGLRenderer(_context);

        _renderView = new RenderView(_display, _context, _renderer);

        _app = new Earth(_renderView, _content, _log);
        _app->resize(_display->getWidth(), _display->getHeight());
    }
}

void EarthActivity::onTermWindow()
{
    _log->info("EarthActivity::onTermWindow()");

    if(_display)
    {
        delete _app;
        delete _renderView;
        delete _renderer;
        delete _context;
        delete _display;
    }
}

void EarthActivity::onWindowResized()
{
    _log->info("EarthActivity::onWindoResize()");

    if(_display)
        _app->resize(_display->getWidth(), _display->getHeight());
}

void EarthActivity::onConfigChanged()
{
    _log->info("EarthActivity::onConfigChanged()");

    if(_display)
    {
        // Switch width <-> height on configuration changed
        _display->resize(_display->getHeight(), _display->getWidth());

        if(getOrientation() == ACONFIGURATION_ORIENTATION_PORT)
            _log->info("Orientation: PORTRAIT; Size: %d, %d", _display->getWidth(), _display->getHeight());
        else if(getOrientation() == ACONFIGURATION_ORIENTATION_LAND)
            _log->info("Orientation: LANDSCAPE; Size: %d, %d", _display->getWidth(), _display->getHeight());

        _app->resize(_display->getWidth(), _display->getHeight());
    }
}

void EarthActivity::onGainedFocus()
{
    _log->info("EarthActivity::onGainedFocus()");
    _hasFocus = true;
    accSetup();
}

void EarthActivity::onLostFocus()
{
    _log->info("EarthActivity::onLostFocus()");
    _hasFocus = false;
    accRelease();
}

void EarthActivity::onStart()
{
    _log->info("EarthActivity::onStart()");
}

void EarthActivity::onResume()
{
    _log->info("EarthActivity::onResume()");
}

void EarthActivity::onSaveState()
{
    _log->info("EarthActivity::onSaveState()");
}

void EarthActivity::onLoadState(void *state)
{
    _log->info("EarthActivity::onLoadState()");
}

void EarthActivity::onPause()
{
    _log->info("EarthActivity::onPause()");
}

void EarthActivity::onStop()
{
    _log->info("EarthActivity::onStop()");
}

void EarthActivity::onDestroy()
{
    _log->info("EarthActivity::onDestroy()");
    _loop = false;
}

void EarthActivity::onEvent()
{
    if(accelerometerSensor != NULL)
    {
        ASensorEvent event;
        while(ASensorEventQueue_getEvents(sensorEventQueue, &event, 1) > 0)
        {
            /*_log->info("accelerometer(x=%f, y=%f, z=%f)",
                event.acceleration.x,
                event.acceleration.y,
                event.acceleration.z);*/
        }
    }
}

int EarthActivity::onInputEvent(AInputEvent* event)
{
    _log->info("EarthActivity::onInputEvent()");

    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
    {
        int x = AMotionEvent_getX(event, 0);
        int y = AMotionEvent_getY(event, 0);
        _log->info("touch(x=%d, y=%d)", x, y);
        return 1;
    }
    return 0;
}

bool EarthActivity::hasFocus() const
{
    return _hasFocus;
}

bool EarthActivity::loop() const
{
    return _loop;
}

void EarthActivity::update(float tick)
{
    if(_display)
    {
        _app->update(tick);
        _app->render();
        _display->swapBuffers();
        _context->checkGlError("app.render()", _log);
    }
}

void EarthActivity::accSetup()
{
    _log->info("EarthActivity::accSetup()");

    if(accelerometerSensor != NULL)
    {
        ASensorEventQueue_enableSensor(sensorEventQueue, accelerometerSensor);

        // We'd like to get 60 events per second (in us).
        ASensorEventQueue_setEventRate(sensorEventQueue, accelerometerSensor, (1000L/60) * 1000);
    }
}

void EarthActivity::accRelease()
{
    _log->info("EarthActivity::accRelease()");

    // When our app loses focus, we stop monitoring the accelerometer.
    // This is to avoid consuming battery while not being used.
    if(accelerometerSensor != NULL)
        ASensorEventQueue_disableSensor(sensorEventQueue, accelerometerSensor);
}

