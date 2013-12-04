#include "GLFWDisplay.hpp"

namespace tigre
{
    namespace gfx
    {
        GLFWDisplay::GLFWDisplay(GLFWwindow *window) :
            _window(window), _width(0), _height(0)
        {
        }

        GLFWDisplay::~GLFWDisplay()
        {
            destroy();
        }

        void GLFWDisplay::init()
        {
            glfwGetWindowSize(_window, &_width, &_height);

            _valid = true;
        }

        void GLFWDisplay::destroy()
        {
        }

        bool GLFWDisplay::valid() const
        {
            return _valid;
        }

        void GLFWDisplay::resize(int width, int height)
        {
            _width = width;
            _height = height;

            glfwSetWindowSize(_window, _width, _height);
        }

        int GLFWDisplay::getWidth() const
        {
            return _width;
        }

        int GLFWDisplay::getHeight() const
        {
            return _height;
        }

        void GLFWDisplay::swapBuffers()
        {
            glfwSwapBuffers(_window);
        }
    }
}
