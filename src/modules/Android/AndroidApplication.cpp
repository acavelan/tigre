/*
TIGRE (https://gitorious.org/tigre) is made available under the MIT License.

Copyright (c) 2012 - 2013 Aurélien Cavelan (razlock)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "AndroidApplication.hpp"

static void _app_handle_cmd(struct android_app *app, int32_t cmd)
{
    AndroidApplication *a = (AndroidApplication*)app->userData;
    switch (cmd)
    {
        case APP_CMD_INPUT_CHANGED:
            a->onInputChanged();
            break;
        case APP_CMD_INIT_WINDOW:
            a->onInitWindow();
            break;
        case APP_CMD_TERM_WINDOW:
            a->onTermWindow();
            break;
        case APP_CMD_WINDOW_RESIZED:
            a->onWindowResized();
            break;
        case APP_CMD_WINDOW_REDRAW_NEEDED:
            a->onWindowRedrawNeeded();
            break;
        case APP_CMD_CONTENT_RECT_CHANGED:
            a->onContentRectChanged();
            break;
        case APP_CMD_GAINED_FOCUS:
            a->onGainedFocus();
            break;
        case APP_CMD_LOST_FOCUS:
            a->onLostFocus();
            break;
        case APP_CMD_CONFIG_CHANGED:
            a->onConfigChanged();
            break;
        case APP_CMD_LOW_MEMORY:
            a->onLowMemory();
            break;
        case APP_CMD_START:
            a->onStart();
            break;
        case APP_CMD_RESUME:
            a->onResume();
            break;
        case APP_CMD_SAVE_STATE:
            a->onSaveState();
            break;
        case APP_CMD_PAUSE:
            a->onPause();
            break;
        case APP_CMD_STOP:
            a->onStop();
            break;
        case APP_CMD_DESTROY:
            a->onDestroy();
            break;
    }
}

static int32_t _app_handle_input(struct android_app *app, AInputEvent *event)
{
    AndroidApplication *application = (AndroidApplication*)app->userData;

    return application->onInputEvent(event);
}

AndroidApplication::AndroidApplication(struct android_app *state, AndroidDisplay *display) :
    _app(state), _display(display), _hasFocus(true), _loop(true)
{
    app_dummy();

    _app->userData = this;
    _app->onAppCmd = _app_handle_cmd;
    _app->onInputEvent = _app_handle_input;

    if (_app->savedState != NULL)
        this->onLoadState(_app->savedState);
}

AndroidApplication::~AndroidApplication()
{
}

void AndroidApplication::pollEvent()
{
    int ident;
    int events;
    struct android_poll_source *source;

    while ((ident = ALooper_pollAll(_hasFocus ? 0 : -1, NULL, &events, (void**)&source)) >= 0)
    {
        if (source != NULL)
            source->process(_app, source);

        if(ident == LOOPER_ID_USER)
            this->onEvent();

        if (_app->destroyRequested != 0)
        {
            this->close();
            return;
        }
    }
}

bool AndroidApplication::hasFocus() const
{
    return _hasFocus;
}

bool AndroidApplication::loop() const
{
    return _loop;
}

void AndroidApplication::close()
{
    _loop = false;
}

struct android_app *AndroidApplication::getState() const
{
    return _app;
}

void AndroidApplication::onInputChanged() {}

void AndroidApplication::onInitWindow()
{
    if(_app->window != NULL)
        _display->initialize(_app->window);
}

void AndroidApplication::onTermWindow()
{
    _display->destroy();
}

void AndroidApplication::onWindowResized() {}

void AndroidApplication::onWindowRedrawNeeded() {}

void AndroidApplication::onContentRectChanged() {}

void AndroidApplication::onGainedFocus()
{
    _hasFocus = true;
}

void AndroidApplication::onLostFocus()
{
    _hasFocus = false;
}

void AndroidApplication::onConfigChanged()
{
	_display->resize(_display->getHeight(), _display->getWidth());
}

void AndroidApplication::onLowMemory() {}

void AndroidApplication::onStart() {}

void AndroidApplication::onResume() {}

void AndroidApplication::onSaveState() {}

void AndroidApplication::onLoadState(void *state) {}

void AndroidApplication::onPause() {}

void AndroidApplication::onStop() {}

void AndroidApplication::onDestroy() {}

void AndroidApplication::onEvent() {}

int AndroidApplication::onInputEvent(AInputEvent* event) {}

int AndroidApplication::getOrientation() const
{
	return AConfiguration_getOrientation(_app->config);
}
