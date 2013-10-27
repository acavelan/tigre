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
    _texture(0), _sphere(0), _defaultShader(0), _noTextureShader(0),
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
    
    ShaderSource defaultShader;
    defaultShader.vertexShader = vertexShader;
    defaultShader.fragmentShader = fragmentShader;
    _defaultShader = _context->createShader(&defaultShader);
    
    ShaderSource noTextureShader;
    noTextureShader.vertexShader = noTextureVertexShader;
    noTextureShader.fragmentShader = noTextureFragmentShader;
    _noTextureShader = _context->createShader(&noTextureShader);
    
    SphereMesh sphereMesh(8, 32, 32);
    _sphere = _renderer->createModelMesh(&sphereMesh);
    
    ImageLoader loader;
    Image *image = loader.loadFromFile("../../media/earth.jpg");
    _texture = _renderer->createTexture2D(image);
    release(image);
    
    _width = _display->getWidth();
    _height = _display->getHeight();
    resize(_width, _height);
    
    _modelMat = glm::scale(mat4(1.0f), vec3(1.0f));
}

void Application::destroy()
{
    _log->info("destroy()\n");
    
    _context->destroy(_defaultShader);
    _context->destroy(_noTextureShader);  
    _renderer->destroy(_sphere);
    _renderer->destroy(_texture);
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
    _angle += delta * 20.0f;
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
    _context->setShader(_defaultShader);
    
    // Earth
    _context->setMatrix4(shader::projection, _projMat);
    _context->setMatrix4(shader::view, _viewMat);
    
    _context->setColor4(shader::color, color::White);
    
    _context->setMatrix4(shader::model, _modelMat);
    
    _renderer->bindTexture(_texture);
    _renderer->draw(_sphere);
    
    // Light
    mat4 light = rotate(mat4(1.0f), _angle, vec3(0.0f, 1.0f, 0.0f));
    light = translate(light, vec3(-10.0f, 5.0f, 0.0f));
    light = scale(light, vec3(0.05f));
	
	_context->setShader(_noTextureShader);
	_context->setMatrix4(shader::projection, _projMat);
    _context->setMatrix4(shader::view, _viewMat);
    _context->setMatrix4(shader::model, light);
    _context->setColor4(shader::color, color::Yellow);
    _renderer->draw(_sphere);
    
    // Texture
    _context->setShader(_defaultShader);
    _context->setMatrix4(shader::projection, _projMat2D);
    _context->setMatrix4(shader::view, _viewMat2D);
    _context->setMatrix4(shader::model, mat4(1.0f));
    _context->setColor4(shader::color, color::White);
    
    _renderer->bindTexture(_texture);
    _renderer->draw(_texture, Rectangle(0, 0, _texture->width/8, _texture->height/8));

	// Limit to 60 FPS
    _display->swapBuffers();
}
