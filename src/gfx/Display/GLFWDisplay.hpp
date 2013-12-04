#ifndef GLFW_DISPLAY_H
#define GLFW_DISPLAY_H

#include <GLFW/glfw3.h>

#include "../Display.hpp"

namespace tigre
{
    namespace gfx
    {
        class GLFWDisplay : public Display
        {
            public:

                GLFWDisplay(GLFWwindow *window);
                ~GLFWDisplay();

                void init();
                void destroy();

                bool valid() const;

                void resize(int width, 	int height);
                int getWidth() const;

                int getHeight() const;

                void swapBuffers();

            private:

                GLFWwindow *_window;
                bool _valid;
                int _width, _height;
        };
    }
}

#endif
