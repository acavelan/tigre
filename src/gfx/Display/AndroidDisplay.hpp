#ifndef ANDROIDDISPLAY_H
#define ANDROIDDISPLAY_H

#include <EGL/egl.h>

#include "../Display.hpp"

namespace tigre
{
    namespace gfx
    {
        class AndroidDisplay : public Display
        {
            public:

                AndroidDisplay(ANativeWindow *window);
                ~AndroidDisplay();

                void setWindow(ANativeWindow *window);

                void resize(int width, int height);

                int getWidth() const;
                int getHeight() const;

                void swapBuffers();

            private:

                ANativeWindow *_window;
                EGLDisplay _display;
                EGLSurface _surface;
                EGLContext _context;

                bool _valid;
                int _width, _height;
        };
    }
}

#endif
