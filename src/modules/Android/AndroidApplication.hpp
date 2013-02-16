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

#ifndef ANDROID_APPLICATION_H
#define ANDROID_APPLICATION_H

#include <android_native_app_glue.h>

#include "../Display/AndroidDisplay.hpp"

/**
 * This class is built over the android_native_app_glue.
 *
 * It provides convenient methods to process both Cmd events,
 * Input Events or custom user events through a C++ / Java like
 * base class.
 */

class AndroidApplication
{
    public:

        AndroidApplication(struct android_app *state, AndroidDisplay *display);
        virtual ~AndroidApplication();

        void pollEvent();

        bool hasFocus() const;

        bool loop() const;

        void close();

        struct android_app *getState() const;

        /**
         * Command from main thread: the AInputQueue has changed.  Upon processing
         * this command, android_app->inputQueue will be updated to the new queue
         * (or NULL).
         */
        virtual void onInputChanged();

        /**
         * Command from main thread: a new ANativeWindow is ready for use. Upon
         * receiving this command, android_app->window will contain the new window
         * surface.
         */
        virtual void onInitWindow();

        /**
         * Command from main thread: the existing ANativeWindow needs to be
         * terminated. Upon receiving this command, android_app->window still
         * contains the existing window; after calling android_app_exec_cmd
         * it will be set to NULL.
         */
        virtual void onTermWindow();

        /**
         * Command from main thread: the current ANativeWindow has been resized.
         * Please redraw with its new size.
         */
        virtual void onWindowResized();

        /**
         * Command from main thread: the system needs that the current ANativeWindow
         * be redrawn.  You should redraw the window before handing this to
         * android_app_exec_cmd() in order to avoid transient drawing glitches.
         */
        virtual void onWindowRedrawNeeded();

        /**
         * Command from main thread: the content area of the window has changed,
         * such as from the soft input window being shown or hidden. You can
         * find the new content rect in android_app::contentRect.
         */
        virtual void onContentRectChanged();

        /**
         * Command from main thread: the app's activity window has gained
         * input focus.
         */
        virtual void onGainedFocus();

        /**
         * Command from main thread: the app's activity window has lost
         * input focus.
         */
        virtual void onLostFocus();

        /**
         * Command from main thread: the current device configuration has changed.
         */
        virtual void onConfigChanged();

        /**
         * Command from main thread: the system is running low on memory.
         * Try to reduce your memory use.
         */
        virtual void onLowMemory();

        /**
         * Command from main thread: the app's activity has been started.
         */
        virtual void onStart();

        /**
         * Command from main thread: the app's activity has been resumed.
         */
        virtual void onResume();

        /**
         * Command from main thread: the app should generate a new saved state
         * for itself, to restore from later if needed. If you have saved state,
         * allocate it with malloc and place it in android_app.savedState with
         * the size in android_app.savedStateSize. It will be freed for you
         * later.
         */
        virtual void onSaveState();

        virtual void onLoadState(void *state);

        /**
         * Command from main thread: the app's activity has been paused.
         */
        virtual void onPause();

        /**
         * Command from main thread: the app's activity has been stopped.
         */
        virtual void onStop();

        /**
         * Command from main thread: the app's activity is being destroyed,
         * and waiting for the app thread to clean up and exit before proceeding.
         */
        virtual void onDestroy();

        /**
         * User defined inputs
         * It is called every time pollEvent() is called
         */
        virtual void onEvent();

        /**
         * Process input events
         */
        virtual int onInputEvent(AInputEvent* event);
        
        int getOrientation() const;

    private:

        struct android_app *_app;

        AndroidDisplay *_display;

        bool _hasFocus;
        bool _loop;

};

#endif
