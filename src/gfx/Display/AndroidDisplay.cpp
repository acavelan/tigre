#include <cstdlib>

#include "AndroidDisplay.hpp"

namespace tigre
{
    namespace gfx
    {
        AndroidDisplay::AndroidDisplay() :
            _window(0), _valid(false), _width(0), _height(0)
        {
        }

        AndroidDisplay::~AndroidDisplay()
        {
            destroy();
        }

        void AndroidDisplay::setWindow(ANativeWindow *window)
        {
            _window = window;
        }

        void AndroidDisplay::init()
        {
            // initialize OpenGL ES and EGL

            /*
             * Here specify the attributes of the desired configuration.
             * Below, we select an EGLConfig with at least 8 bits per color
             * component compatible with on-screen windows
             */
            const EGLint attribs[] =
            {
                EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
                EGL_BLUE_SIZE, 8,
                EGL_GREEN_SIZE, 8,
                EGL_RED_SIZE, 8,
                EGL_ALPHA_SIZE, 0,
                EGL_DEPTH_SIZE, 2,
                EGL_STENCIL_SIZE, 2,
                EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
                EGL_NONE
            };

            EGLint w, h, dummy, format;
            EGLint numConfigs;
            EGLConfig config;
            EGLSurface surface;
            EGLContext context;

            EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);

            eglInitialize(display, 0, 0);

            /* Here, the application chooses the configuration it desires. In this
             * sample, we have a very simplified selection process, where we pick
             * the first EGLConfig that matches our criteria */
            eglChooseConfig(display, attribs, &config, 1, &numConfigs);

            /* EGL_NATIVE_VISUAL_ID is an attribute of the EGLConfig that is
             * guaranteed to be accepted by ANativeWindow_setBuffersGeometry().
             * As soon as we picked a EGLConfig, we can safely reconfigure the
             * ANativeWindow buffers to match, using EGL_NATIVE_VISUAL_ID. */
            eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);

            ANativeWindow_setBuffersGeometry(_window, 0, 0, format);

            surface = eglCreateWindowSurface(display, config, _window, NULL);

            EGLint contextAttrs[] =
            {
                EGL_CONTEXT_CLIENT_VERSION, 2,
                EGL_NONE
            };

            context = eglCreateContext(display, config, NULL, contextAttrs);

            if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
            {
                //Log::error("Unable to eglMakeCurrent");
            }

            eglQuerySurface(display, surface, EGL_WIDTH, &w);
            eglQuerySurface(display, surface, EGL_HEIGHT, &h);

            _display = display;
            _context = context;
            _surface = surface;
            _width = w;
            _height = h;

            _valid = true;
        }

        void AndroidDisplay::destroy()
        {
            if (_display != EGL_NO_DISPLAY)
            {
                eglMakeCurrent(_display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
                if (_context != EGL_NO_CONTEXT)
                {
                    eglDestroyContext(_display, _context);
                }
                if (_surface != EGL_NO_SURFACE)
                {
                    eglDestroySurface(_display, _surface);
                }
                eglTerminate(_display);
            }

            _display = EGL_NO_DISPLAY;
            _context = EGL_NO_CONTEXT;
            _surface = EGL_NO_SURFACE;
        }

        bool AndroidDisplay::valid() const
        {
            return _valid;
        }

        void AndroidDisplay::resize(int width, int height)
        {
            _width = width;
            _height = height;
        }

        int AndroidDisplay::getWidth() const
        {
            return _width;
        }

        int AndroidDisplay::getHeight() const
        {
            return _height;
        }

        void AndroidDisplay::swapBuffers()
        {
            eglSwapBuffers(_display, _surface);
        }
    }
}
