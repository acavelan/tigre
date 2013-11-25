#include "Application.hpp"

Application::Application(Display *display, 
						 Context *context, 
						 Renderer *renderer, 
						 Content *content, 
						 Logger *logger) :
    Game(display, context, renderer, content), _log(logger),
    _earthTex(0), _whiteTex(0), _sphere(0), _shader(0), _angle(0.0f)
{
    _log->info("Application(log, display, context, renderer, content)\n");
}

Application::~Application()
{
}

void Application::start()
{
	_log->info("start()\n");
	
	_sphere = loadSphere(8, 32, 32);
    _earthTex = loadTexture("content:textures/earth.jpg");
    _whiteTex = loadTexture("content:textures/white1x1.jpg");
    _shader = loadShader("shaders:texture.vert", "shaders:texture.frag");
}

void Application::stop()
{
	_log->info("stop()\n");
    
    destroy(_sphere);
    destroy(_earthTex);
    destroy(_whiteTex);
    destroy(_shader); 
}

void Application::resize(int width, int height)
{
	_log->info("resize(%d, %d)\n", width, height);
	
	setViewport(width, height);
		
	_projection = perspective(60.0f, (float)width / (float)height, 0.001f, 100000.f);
	_projection2D = ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 10.0f);
	
	_view = lookAt(vec3(20.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	_view2D = lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
}

void Application::update(float delta)
{	
    _angle += delta * 15.0f;
    
    if(_angle > 360) _angle = 0;
}

void Application::drawFrame()
{	
    clear(color::Black);
    setShader(_shader, _projection, _view, color::White);
    
    // Earth
    mat4 model= rotate(mat4(1.0f), 23.0f, vec3(0.0f, 0.0f, 1.0f));
    model = rotate(model, _angle, vec3(0.0f, 1.0f, 0.0f));
    
    setMatrix4(shader::model, model);
    
    bindTexture(_earthTex);
    draw(_sphere);
    
    // Light
    model = rotate(mat4(1.0f), _angle, vec3(0.0f, 1.0f, 0.0f));
    model = translate(model, vec3(-10.0f, 5.0f, 0.0f));
    model = scale(model, vec3(0.05f));
	
    setMatrix4(shader::model, model);
    setColor(color::Yellow);
    
    bindTexture(_whiteTex);
    draw(_sphere);
    
    // Texture
    setShader(_shader, _projection2D, _view2D, color::White);
    
    bindTexture(_earthTex);
    draw(_earthTex, Rectangle(0, 0, _earthTex->width/8, _earthTex->height/8));
}
