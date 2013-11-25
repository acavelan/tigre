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

#include "Activity.hpp"
#include "activity.hpp"

namespace tigre
{
	namespace os
	{
		namespace android
		{
			static void _app_handle_cmd(struct android_app *app, int32_t cmd)
			{
				Activity *a = (Activity*)app->userData;
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
				Activity *activity = (Activity*)app->userData;

				return activity->onInputEvent(event);
			}

			Activity::Activity(struct android_app *state) :
				_app(state)
			{
				app_dummy();

				_app->userData = this;
				_app->onAppCmd = _app_handle_cmd;
				_app->onInputEvent = _app_handle_input;

				if(_app->savedState != NULL)
					this->onLoadState(_app->savedState);
				
				cacheActivity(state->activity);
			}

			Activity::~Activity()
			{
			}

			void Activity::pollEvent()
			{
				int ident;
				int events;
				struct android_poll_source *source;

				while((ident = ALooper_pollAll(0, NULL, &events, (void**)&source)) >= 0)
				{
					if(source != NULL)
						source->process(_app, source);

					if(ident == LOOPER_ID_USER)
						this->onEvent();

					if(_app->destroyRequested != 0)
					{
						onDestroy();
						return;
					}
				}
			}

			struct android_app *Activity::getState() const
			{
				return _app;
			}

			void Activity::onInputChanged() {}

			void Activity::onInitWindow() {}

			void Activity::onTermWindow() {}

			void Activity::onWindowResized() {}

			void Activity::onWindowRedrawNeeded() {}

			void Activity::onContentRectChanged() {}

			void Activity::onGainedFocus() {}

			void Activity::onLostFocus() {}

			void Activity::onConfigChanged() {}

			void Activity::onLowMemory() {}

			void Activity::onStart() {}

			void Activity::onResume() {}

			void Activity::onSaveState() {}

			void Activity::onLoadState(void *state) {}

			void Activity::onPause() {}

			void Activity::onStop() {}

			void Activity::onDestroy() {}

			void Activity::onEvent() {}

			int Activity::onInputEvent(AInputEvent* event) {}

			int Activity::getOrientation() const
			{
				return AConfiguration_getOrientation(_app->config);
			}
		}
	}
}
