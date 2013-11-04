#ifndef CONTENT_H
#define CONTENT_H

#include "user/core.hpp"
#include "user/gfx.hpp"

#include "Sphere.hpp"

using namespace tigre;

class Content : public core::ContentLoader<gfx::Image>
{
	public:
		
		Content(gfx::Context *context, gfx::Renderer *renderer) : 
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
		
		gfx::Texture2D *createTexture(const std::string &filename)
		{
			gfx::Image *image = load<gfx::Image>(filename);
			gfx::Texture2D *texture = _renderer->createTexture2D(image);
			release(image);
			return texture;
		}
		
		void destroy(gfx::Texture2D *texture)
		{
			_renderer->destroy(texture);
		}
		
		gfx::Shader *createShader(const std::string &vertexFile, const std::string &fragmentFile)
		{
			gfx::ShaderSource shaderSource;
			shaderSource.vertexShader = core::loadFile(vertexFile);
			shaderSource.fragmentShader = core::loadFile(fragmentFile);
			
			gfx::Shader *shader = _context->createShader(shaderSource);
			
			return shader;
		}
		
		void destroy(gfx::Shader *shader)
		{
			_context->destroy(shader);
		}
		
		gfx::ModelMesh *createSphere(float radius, int latitudeBands, int longitudeBands)
		{
			Sphere sphere(radius, latitudeBands, longitudeBands);
			gfx::ModelMesh *model = _renderer->createModelMesh(&sphere);
			return model;
		}
		
		void destroy(gfx::ModelMesh *model)
		{
			_renderer->destroy(model);
		}
	
	private:
		
		gfx::Context *_context;
		gfx::Renderer *_renderer;
};

#endif
