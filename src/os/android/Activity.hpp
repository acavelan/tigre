#ifndef ANDROID_Activity_H
#define ANDROID_Activity_H

#include <android_native_app_glue.h>

/**
 * This class is built over the android_native_app_glue.
 *
 * It provides convenient methods to process both Cmd events,
 * Input Events or custom user events through a C++ / Java like
 * base class.
 */

namespace tigre
{
    namespace os
    {
        namespace android
        {
            class Activity
            {
                public:

                    Activity(struct android_app *state);
                    virtual ~Activity();

                    void pollEvent();

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

            };
        }
    }
}

#endif
