/*
TIGRE (https://gitorious.org/tigre) is made available under the MIT License.

Copyright (c) 2012 - 2013 Aurélien Cavelan (razlock)

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Game.hpp"
#include "../core/file.hpp"
#include "../gfx/Image.hpp"

namespace tigre
{
	namespace game
	{
		Game::Game(gfx::Display *display, gfx::Context *context, gfx::Renderer *renderer, Content *content) :
			 _display(display), _context(context), _renderer(renderer), _content(content)
		{
		}

		Game::~Game()
		{
		}
		
		void Game::resize(int width, int height)
		{
			_display->resize(width, height);
		}
				
		int Game::getWidth() const
		{
			return _display->getWidth();
		}
		
		int Game::getHeight() const
		{
			return _display->getHeight();
		}
				
		void Game::setViewport(int x, int y, int width, int height)
		{
			_context->setViewport(x, y, width, height);
		}
		
		void Game::setViewport(int width, int height)
		{
			_context->setViewport(width, height);
		}

		int Game::getViewPortX() const
		{
			return _context->getViewPortX();
		}
		
		int Game::getViewPortY() const
		{
			return _context->getViewPortY();
		}

		int Game::getViewPortWidth() const
		{
			return _context->getViewPortWidth();
		}
		
		int Game::getViewPortHeight() const
		{
			return _context->getViewPortHeight();
		}
		
		void Game::setMatrix4(int port, const glm::mat4 &mat)
		{
			_context->setMatrix4(port, mat);
		}
		
		void Game::setFloat4(int port, float a, float b, float c, float d)
		{
			_context->setFloat4(port, a, b, c, d);
		}
		
		void Game::setColor(const gfx::Color &color)
		{
			_context->setFloat4(gfx::shader::color, color.r, color.g, color.b, color.a);
		}
		
		void Game::clear(const gfx::Color &color)
		{
			_context->clear(color);
		}
		
		gfx::Shader* Game::createShader(const gfx::ShaderSource &shaderSource)
		{
			return _context->createShader(shaderSource);
		}
		
		void Game::destroy(gfx::Shader *shader)
		{
			_context->destroy(shader);
		}
		
		void Game::setShader(gfx::Shader *shader)
		{
			_context->setShader(shader);
		}
		
		void Game::setShader(gfx::Shader *shader, const gfx::Color &color)
		{
			_context->setShader(shader);
			_context->setFloat4(gfx::shader::color, color.r, color.g, color.b, color.a);
		}
		
		void Game::setShader(gfx::Shader *shader, const glm::mat4 &projection, const glm::mat4 &view)
		{
			_context->setShader(shader);
			_context->setMatrix4(gfx::shader::projection, projection);
			_context->setMatrix4(gfx::shader::view, view);
		}
		
		void Game::setShader(gfx::Shader *shader, const glm::mat4 &projection, const glm::mat4 &view, const gfx::Color &color)
		{
			_context->setShader(shader);
			_context->setMatrix4(gfx::shader::projection, projection);
			_context->setMatrix4(gfx::shader::view, view);
			_context->setFloat4(gfx::shader::color, color.r, color.g, color.b, color.a);
		}
				
		gfx::Texture2D* Game::createTexture2D(gfx::Image *image)
		{
			return _renderer->createTexture2D(image);
		}
		
		void Game::bindTexture(gfx::Texture2D *texture)
		{
			_renderer->bindTexture(texture);
		}
		
		void Game::draw(gfx::Texture2D *texture)
		{
			_renderer->draw(texture);
		}
		
		void Game::draw(gfx::Texture2D *texture, gfx::Rectangle target)
		{
			_renderer->draw(texture, target);
		}
		
		void Game::draw(gfx::Texture2D *texture, gfx::Rectangle origin, gfx::Rectangle target)
		{
			_renderer->draw(texture, origin, target);
		}
		
		void Game::destroy(gfx::Texture2D *texture)
		{
			_renderer->destroy(texture);
		}
		
		gfx::ModelMesh* Game::createModelMesh(gfx::Mesh *mesh)
		{
			return _renderer->createModelMesh(mesh);
		}
		
		void Game::draw(gfx::ModelMesh *model)
		{
			_renderer->draw(model);
		}
		
		void Game::destroy(gfx::ModelMesh *model)
		{
			_renderer->destroy(model);
		}
		
		gfx::ModelMesh* Game::loadSphere(float radius, int lat, int lon)
		{
			Sphere sphere(radius, lat, lon);
			return createModelMesh(&sphere);
		}

		gfx::Texture2D* Game::loadTexture(const std::string &filename)
		{
			gfx::Image *image = _content->load<gfx::Image>(filename);
			
			gfx::Texture2D *texture = _renderer->createTexture2D(image);
			
			release(image);
			
			return texture;
		}

		gfx::Shader* Game::loadShader(const std::string &vertexFile, const std::string &fragmentFile)
		{
			gfx::ShaderSource shaderSource;
			
			_content->loadFile(vertexFile, shaderSource.vertexShader);
			_content->loadFile(fragmentFile, shaderSource.fragmentShader);
			
			gfx::Shader *shader = _context->createShader(shaderSource);
			
			return shader;
		}
	}
}
