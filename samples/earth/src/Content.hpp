#ifndef CONTENT_H
#define CONTENT_H

#include "user/core.hpp"
#include "user/graphics.hpp"

#include "Sphere.hpp"

using namespace tigre;

class Content : public core::ContentLoader<graphics::Image>
{
	public:
		
		Content(graphics::Context *context, graphics::Renderer *renderer) : 
			_context(context), _renderer(renderer)
		{
		}
		
		template<class T>
		T* load(const std::string &filename)
		{
			return ContentLoader<T>::load(filename);
		}
		
		template<class T>
		void save(const std::string &filename, const T *resource)
		{
			ContentLoader<T>::save(filename, resource);
		}
		
		graphics::Texture2D *createTexture(const std::string &filename)
		{
			graphics::Image *image = load<graphics::Image>(filename);
			graphics::Texture2D *texture = _renderer->createTexture2D(image);
			release(image);
			return texture;
		}
		
		void destroy(graphics::Texture2D *texture)
		{
			_renderer->destroy(texture);
		}
		
		graphics::Shader *createShader(const std::string &vertexFile, const std::string &fragmentFile)
		{
			graphics::ShaderSource shaderSource;
			shaderSource.vertexShader = core::loadFile(vertexFile);
			shaderSource.fragmentShader = core::loadFile(fragmentFile);
			
			graphics::Shader *shader = _context->createShader(shaderSource);
			
			return shader;
		}
		
		void destroy(graphics::Shader *shader)
		{
			_context->destroy(shader);
		}
		
		graphics::ModelMesh *createSphere(float radius, int latitudeBands, int longitudeBands)
		{
			Sphere sphere(radius, latitudeBands, longitudeBands);
			graphics::ModelMesh *model = _renderer->createModelMesh(&sphere);
			return model;
		}
		
		void destroy(graphics::ModelMesh *model)
		{
			_renderer->destroy(model);
		}
	
	private:
		
		graphics::Context *_context;
		graphics::Renderer *_renderer;
};

#endif
