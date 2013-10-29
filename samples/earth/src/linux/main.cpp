#include <GLFW/glfw3.h>

#include "Application.hpp"

#include "conv/string.hpp"
#include "core/Exceptions.hpp"
#include "utils/Logger/ConsoleLogger.hpp"
#include "graphics/Display/GLFWDisplay.hpp"
#include "graphics/Context/OpenGLContext.hpp"
#include "graphics/Renderer/OpenGLRenderer.hpp"

#include "kit/Content.hpp"

using namespace tigre;

Application *handler = 0;

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
		width = conv::toInt(argv[1]);
		height = conv::toInt(argv[2]);
		if(argc > 3)
			monitor = glfwGetPrimaryMonitor();
	}
        
	window = glfwCreateWindow(width, height, "Game", monitor, 0);
    
    if(!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowSizeCallback(window, onResize);
    glfwMakeContextCurrent(window);
    
	utils::ConsoleLogger appLogger("Application"), mainLogger("main");
	
	graphics::GLFWDisplay display(window);
	graphics::OpenGLContext context(&display);
	graphics::OpenGLRenderer renderer(&context); 
	
	display.init();
	context.init();
	renderer.init();
	
	context.printGLString(GL_VENDOR, &appLogger);
	context.printGLString(GL_RENDERER, &appLogger);
	context.printGLString(GL_VERSION, &appLogger);
	context.printGLString(GL_SHADING_LANGUAGE_VERSION, &appLogger);
	
	kit::Content content(&renderer);
	
	Application app(&appLogger, &display, &context, &renderer, &content);
	handler = &app;
	
	try
	{
		app.init();
		context.checkGlError("create()", &mainLogger);
		
		tigre::utils::Timer timer;
		timer.start();

		bool run = true;
		while(run)
		{		
			app.update(timer.tick());
			app.drawFrame();
			context.checkGlError("drawFrame()", &mainLogger);
			
			run = !(glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window));
			
			glfwPollEvents();
		}
	}
	catch(const core::Exception &e)
	{
		appLogger.error(e.what());
	}
	
	glfwTerminate();
	
	return 0;
}
