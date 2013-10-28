#include <cstdlib>
#include <sys/time.h>
#include <unistd.h>

#include <glm/gtc/matrix_transform.hpp>

#include "graphics/ImageLoader.hpp"
#include "graphics/Image.hpp"
#include "graphics/Rectangle.hpp"

#include "Application.hpp"
#include "SphereMesh.hpp"
#include "Shaders.hpp"
    
using namespace glm;
using namespace tigre;
using namespace core;
using namespace graphics;
using namespace resource;

Application::Application(	utils::Logger *log,
							Display *display, 
							Context *context,
							Renderer *renderer) :
    _log(log), _display(display), _context(context), _renderer(renderer),
    _earthTex(0), _sphere(0), _shader(0), 
    _width(0), _height(0), _FPS(0), _timer(0.0f), _angle(0)
{
    _log->info("Application(log, display, context, renderer)\n");
}

Application::~Application()
{
	destroy();
}

void Application::init()
{	
    _log->info("create()\n");
    
    ShaderSource shader;
    shader.vertexShader = vertexShader;
    shader.fragmentShader = fragmentShader;
    _shader = _context->createShader(&shader);
    
    SphereMesh sphereMesh(8, 32, 32);
    _sphere = _renderer->createModelMesh(&sphereMesh);
    
    ImageLoader loader;
    Image *image = loader.loadFromFile("../../media/earth.jpg");
    _earthTex = _renderer->createTexture2D(image);
    release(image);
    
    image = loader.loadFromFile("../../media/white1x1.jpg");
    _whiteTex = _renderer->createTexture2D(image);
    release(image);
    
    _width = _display->getWidth();
    _height = _display->getHeight();
    resize(_width, _height);
    
    _modelMat = glm::scale(mat4(1.0f), vec3(1.0f));
}

void Application::destroy()
{
    _log->info("destroy()\n");
    
    _context->destroy(_shader); 
    _renderer->destroy(_sphere);
    _renderer->destroy(_earthTex);
    _renderer->destroy(_whiteTex);
}

void Application::resize(int width, int height)
{
	_log->info("resize(%d, %d)\n", width, height);
	
	_context->setViewport(width, height);
		
	_projMat = perspective(60.0f, (float)_context->getWidth() / (float)_context->getHeight(), 0.001f, 100000.f);
	_projMat2D = ortho(0.0f, (float)width, 0.0f, (float)height, 0.0f, 10.0f);
	
	_viewMat = lookAt(vec3(20.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
	_viewMat2D = lookAt(vec3(0.0f, 0.0f, 5.0f), vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 1.0f, 0.0f));
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

    // Update all matrices
    mat4 modelTranslate = scale(mat4(1.0f), vec3(1.0f));
    mat4 modelRotate = rotate(modelRotate, 23.0f, vec3(0.0f, 0.0f, 1.0f));
    modelRotate = rotate(modelTranslate, _angle, vec3(0.0f, 1.0f, 0.0f));
    _modelMat = modelRotate;
}

void Application::drawFrame()
{	
    _context->clear(color::Black);
    _context->setShader(_shader);
    
    // Earth
    _context->setMatrix4(shader::projection, _projMat);
    _context->setMatrix4(shader::view, _viewMat);
    
    _context->setColor4(shader::color, color::White);
    
    _context->setMatrix4(shader::model, _modelMat);
    
    _renderer->bindTexture(_earthTex);
    _renderer->draw(_sphere);
    
    // Light
    mat4 light = rotate(mat4(1.0f), _angle, vec3(0.0f, 1.0f, 0.0f));
    light = translate(light, vec3(-10.0f, 5.0f, 0.0f));
    light = scale(light, vec3(0.05f));
	
    _context->setMatrix4(shader::model, light);
    _context->setColor4(shader::color, color::Yellow);
    _renderer->bindTexture(_whiteTex);
    _renderer->draw(_sphere);
    
    // Texture
    _context->setMatrix4(shader::projection, _projMat2D);
    _context->setMatrix4(shader::view, _viewMat2D);
    _context->setMatrix4(shader::model, mat4(1.0f));
    _context->setColor4(shader::color, color::White);
    
    _renderer->bindTexture(_earthTex);
    _renderer->draw(_earthTex, Rectangle(0, 0, _earthTex->width/8, _earthTex->height/8));

	// Limit to 60 FPS
    _display->swapBuffers();
}
