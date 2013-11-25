#include "AppHandler.hpp"

AppHandler::AppHandler(	struct android_app *state, 
                        Logger *log,
                        AndroidDisplay *display,
                        OpenGLContext *context,
                        OpenGLRenderer *renderer,
                        Application *app) :
    Activity(state), _log(log), _display(display), _context(context), _renderer(renderer), _app(app), _hasFocus(true), _loop(true)
{
    _log->info("AppHandler::AppHandler(state, log, display)");
	
    sensorManager = ASensorManager_getInstance();
    accelerometerSensor = ASensorManager_getDefaultSensor(sensorManager, ASENSOR_TYPE_ACCELEROMETER);
    sensorEventQueue = ASensorManager_createEventQueue(sensorManager, getState()->looper, LOOPER_ID_USER, NULL, NULL);
}

AppHandler::~AppHandler()
{
    _log->info("AppHandler::~AppHandler()");
}

void AppHandler::onInitWindow()
{
    _log->info("AppHandler::onInitWindow()");
    
    if(getState()->window != NULL)
    {
		_display->setWindow(getState()->window);
        _display->init();
        _context->init();
        _renderer->init();

        _context->printGLString(GL_VENDOR, _log);
		_context->printGLString(GL_RENDERER, _log);
		_context->printGLString(GL_VERSION, _log);
		_context->printGLString(GL_SHADING_LANGUAGE_VERSION, _log);
		
		_app->start();
		_app->resize(_display->getWidth(), _display->getHeight());
	}
}

void AppHandler::onTermWindow()
{
    _log->info("AppHandler::onTermWindow()");
    
    if(_display->valid())
		_app->stop();
			
	_renderer->destroy();
	_context->destroy();
    _display->destroy();
}

void AppHandler::onWindowResized()
{
    _log->info("AppHandler::onWindoResize()");
    if(_display->valid())
		_app->resize(_display->getWidth(), _display->getHeight());
}

void AppHandler::onConfigChanged()
{
    _log->info("AppHandler::onConfigChanged()");
    
    if(_display->valid())
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

void AppHandler::onGainedFocus()
{
    _log->info("AppHandler::onGainedFocus()");
    _hasFocus = true;
    accSetup();
}

void AppHandler::onLostFocus()
{
    _log->info("AppHandler::onLostFocus()");
    _hasFocus = false;
    accRelease();
}

void AppHandler::onStart()
{
    _log->info("AppHandler::onStart()");
}

void AppHandler::onResume()
{
    _log->info("AppHandler::onResume()");
}

void AppHandler::onSaveState()
{
    _log->info("AppHandler::onSaveState()");
}

void AppHandler::onLoadState(void *state)
{
    _log->info("AppHandler::onLoadState()");
}

void AppHandler::onPause()
{
    _log->info("AppHandler::onPause()");
}

void AppHandler::onStop()
{
    _log->info("AppHandler::onStop()");
}

void AppHandler::onDestroy()
{
    _log->info("AppHandler::onDestroy()");
    close();
}

void AppHandler::onEvent()
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

int AppHandler::onInputEvent(AInputEvent* event)
{
    _log->info("AppHandler::onInputEvent()");

    if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
    {
        int x = AMotionEvent_getX(event, 0);
        int y = AMotionEvent_getY(event, 0);
        _log->info("touch(x=%d, y=%d)", x, y);
        return 1;
    }
    return 0;
}

bool AppHandler::hasFocus() const
{
    return _hasFocus;
}

bool AppHandler::loop() const
{
    return _loop;
}

void AppHandler::close()
{
    _loop = false;
}

void AppHandler::accSetup()
{
    _log->info("AppHandler::accSetup()");

    if(accelerometerSensor != NULL)
    {
        ASensorEventQueue_enableSensor(sensorEventQueue, accelerometerSensor);

        // We'd like to get 60 events per second (in us).
        ASensorEventQueue_setEventRate(sensorEventQueue, accelerometerSensor, (1000L/60) * 1000);
    }
}

void AppHandler::accRelease()
{
    _log->info("AppHandler::accRelease()");

    // When our app loses focus, we stop monitoring the accelerometer.
    // This is to avoid consuming battery while not being used.
    if(accelerometerSensor != NULL)
        ASensorEventQueue_disableSensor(sensorEventQueue, accelerometerSensor);
}

