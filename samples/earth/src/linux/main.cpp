#include <GLFW/glfw3.h>

#include "user/core.hpp"
#include "user/graphics.hpp"
#include "core/Logger/ConsoleLogger.hpp"
#include "graphics/Display/GLFWDisplay.hpp"
#include "graphics/Context/OpenGLContext.hpp"
#include "graphics/Renderer/OpenGLRenderer.hpp"

#include "Content.hpp"
#include "Application.hpp"

using namespace tigre;
using namespace core;
using namespace graphics;

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
		width = toInt(argv[1]);
		height = toInt(argv[2]);
		if(argc > 3)
			monitor = glfwGetPrimaryMonitor();
	}
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    
	window = glfwCreateWindow(width, height, "Game", monitor, 0);
    
    if(!window)
    {
        glfwTerminate();
        return -1;
    }
    
    glfwSetWindowSizeCallback(window, onResize);
    glfwMakeContextCurrent(window);
    
	ConsoleLogger logger("Application");
	
	GLFWDisplay display(window);
	OpenGLContext context(&display);
	OpenGLRenderer renderer(&context); 
	
	display.init();
	context.init();
	renderer.init();
	
	context.printGLString(GL_VENDOR, &logger);
	context.printGLString(GL_RENDERER, &logger);
	context.printGLString(GL_VERSION, &logger);
	context.printGLString(GL_SHADING_LANGUAGE_VERSION, &logger);
	
	Content content(&context, &renderer);
	content.registerLoader(new ImageLoader(), "jpg,bmp,png,tga");
	
	Application app(&display, &context, &renderer, &logger, &content);
	handler = &app;
	
	try
	{
		app.init();
		context.checkGlError("create()", &logger);
		
		Timer timer;
		timer.start();

		bool run = true;
		while(run)
		{		
			app.update(timer.tick());
			app.drawFrame();
			context.checkGlError("drawFrame()", &logger);
			
			run = !(glfwGetKey(window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(window));
			
			glfwPollEvents();
		}
	}
	catch(const core::Exception &e)
	{
		logger.error(e.what());
	}
	
	glfwTerminate();
	
	return 0;
}
