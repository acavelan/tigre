#include <GLFW/glfw3.h>
#include <cstdio>

#include "core/core.hpp"
#include "gfx/gfx.hpp"
#include "hl/hl.hpp"

#include "core/Logger/ConsoleLogger.hpp"
#include "gfx/Display/GLFWDisplay.hpp"
#include "gfx/Context/OpenGLContext.hpp"
#include "gfx/Renderer/OpenGLRenderer.hpp"

#include "Earth.hpp"

using namespace tigre::core;
using namespace tigre::gfx;
using namespace tigre::hl;

Earth *handler = 0;

void onResize(GLFWwindow*, int width, int height)
{
    handler->resize(width, height);
}

int main(int argc, char **argv)
{
    GLFWwindow *window = 0;
    GLFWmonitor *monitor = 0;

    int width = 800;
    int height = 600;

    if(!glfwInit())
        return -1;

    if(argc > 2)
    {
        width = toInt(argv[1]);
        height = toInt(argv[2]);
        if(argc > 3)
            monitor = glfwGetPrimaryMonitor();
    }

    glfwWindowHint(GLFW_SAMPLES, 4);

    window = glfwCreateWindow(width, height, "Tigre", monitor, 0);

    if(!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetWindowSizeCallback(window, onResize);
    glfwMakeContextCurrent(window);

    ConsoleLogger logger("Tigre");
    
    try
    {
        OpenGLContext context;
        GLFWDisplay display(window);
        OpenGLRenderer renderer(&context);

        context.printGLString(GL_VENDOR, &logger);
        context.printGLString(GL_RENDERER, &logger);
        context.printGLString(GL_VERSION, &logger);
        context.printGLString(GL_SHADING_LANGUAGE_VERSION, &logger);

        Content content;
        content.addLocation("content", "../../content");
        content.addLocation("shaders", "../../content/shaders/130");
        content.registerLoader(new ImageLoader(), "jpg,bmp,png,tga");

        RenderView renderView(&display, &context, &renderer);

        Earth app(&renderView, &content, &logger);
        handler = &app;

        app.resize(width, height);
        context.checkGlError("create()", &logger);

        Timer timer;
        timer.start();

        float delta = 0.0f, sec = 0.0f;
        int frames = 0;

        bool run = true;
        while(run)
        {
            delta = timer.tick();

            sec += delta;

            if(sec > 1.0f)
            {
                char title[32];
                sprintf(title, "Tigre: %d FPS", frames);
                glfwSetWindowTitle(window, title);

                sec = 0.0f;
                frames = 0;
            }
            else
                frames++;

            app.update(delta);
            app.render();
            display.swapBuffers();
            context.checkGlError("app.render()", &logger);

            run = !(glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window));

            glfwPollEvents();
        }
    }
    catch(const Exception &e)
    {
        logger.error(e.what());
    }

    glfwTerminate();

    return 0;
}
