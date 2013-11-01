#include <cstdlib>
#include <sys/time.h>
#include <unistd.h>

#include <glm/gtc/matrix_transform.hpp>

#include "core/file.hpp"
#include "graphics/Rectangle.hpp"

#include "Application.hpp"
#include "SphereMesh.hpp"

using namespace std;
using namespace glm;
using namespace core;
using namespace graphics;

Application::Application(	Display *display, 
							Context *context,
							Renderer *renderer,
							Logger *logger,
							Content *content) :
    _display(display), _context(context), _renderer(renderer), _log(logger), 
    _content(content), _earthTex(0), _whiteTex(0), _sphere(0), _shader(0), 
    _width(0), _height(0), _FPS(0), _timer(0.0f), _angle(0)
{
    _log->info("Application(log, display, context, renderer, content)\n");
}

Application::~Application()
{
	destroy();
}

void Application::init()
{	
    _log->info("create()\n");
    
    SphereMesh sphereMesh(8, 32, 32);
    _sphere = _renderer->createModelMesh(&sphereMesh);
    
    ShaderSource shaderSource;
    shaderSource.vertexShader = loadFile("../../content/shaders/texture.vert");
    shaderSource.fragmentShader = loadFile("../../content/shaders/texture.frag");
    _shader = _context->createShader(shaderSource);
    
    Image *image = _content->load<Image>("../../content/textures/earth.jpg");
    _earthTex = _renderer->createTexture2D(image);
    release(image);
    
    image = _content->load<Image>("../../content/textures/white1x1.jpg");
    _whiteTex = _renderer->createTexture2D(image);
    release(image);
    
    _width = _display->getWidth();
    _height = _display->getHeight();
    
    resize(_width, _height);
}

void Application::destroy()
{
    _log->info("destroy()\n");
    
    _context->destroy(_shader); 
    _renderer->destroy(_earthTex);
    _renderer->destroy(_whiteTex);
    _renderer->destroy(_sphere);
}

void Application::resize(int width, int height)
{
	_log->info("resize(%d, %d)\n", width, height);
	
	_context->setViewport(width, height);
		
	_projection = perspective(60.0f, (float)_context->getWidth() / (float)_context->getHeight(), 0.001f, 100000.f);
	_projection2D = ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 10.0f);
	
	_view = lookAt(vec3(20.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	_view2D = lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
}

void Application::update(float delta)
{
	_timer += delta;
	if(_timer > 1.0f)
	{
		_log->info("FPS: %d\n", _FPS);
		_timer = 0.0f;
        _FPS = 0;
	}
	else
		_FPS++;
	
    // Animation
    _angle += delta * 15.0f;
    if(_angle > 360)
        _angle = 0;
}

void Application::drawFrame()
{	
    _context->clear(color::Black);
    _context->setShader(_shader, color::White);
    _context->setMatrix4(shader::projection, _projection);
    _context->setMatrix4(shader::view, _view);
    
    // Earth
    mat4 model= rotate(mat4(1.0f), 23.0f, vec3(0.0f, 0.0f, 1.0f));
    model = rotate(model, _angle, vec3(0.0f, 1.0f, 0.0f));
    
    _context->setMatrix4(shader::model, model);
    
    _renderer->bindTexture(_earthTex);
    _renderer->draw(_sphere);
    
    // Light
    model = rotate(mat4(1.0f), _angle, vec3(0.0f, 1.0f, 0.0f));
    model = translate(model, vec3(-10.0f, 5.0f, 0.0f));
    model = scale(model, vec3(0.05f));
	
    _context->setMatrix4(shader::model, model);
    _context->setColor(color::Yellow);
    
    _renderer->bindTexture(_whiteTex);
    _renderer->draw(_sphere);
    
    // Texture
    _context->setMatrix4(shader::projection, _projection2D);
    _context->setMatrix4(shader::view, _view2D);
    _context->setColor(color::White);
    
    _renderer->bindTexture(_earthTex);
    _renderer->draw(_earthTex, Rectangle(0, 0, _earthTex->width/8, _earthTex->height/8));

	// Limit to 60 FPS
    _display->swapBuffers();
}
