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

#ifndef GAME_H
#define GAME_H

#include "../gfx/Display.hpp"
#include "../gfx/Context.hpp"
#include "../gfx/Renderer.hpp"
#include "../core/Logger.hpp"
#include "Content.hpp"
#include "Sphere.hpp"

namespace tigre
{
	namespace game
	{
		class Game : public gfx::Display,
					 public gfx::Context,
					 public gfx::Renderer,
					 public Content
		{
			public:
				
				Game(gfx::Display *display, gfx::Context *context, gfx::Renderer *renderer, Content *content);
				
				virtual ~Game();
			
				// Display
				void resize(int width, int height);
				
				int getWidth() const;
				int getHeight() const;
				
				// Context
				void setViewport(int x, int y, int width, int height);
				void setViewport(int width, int height);

				int getViewPortX() const;
				int getViewPortY() const;

				int getViewPortWidth() const;
				int getViewPortHeight() const;
				
				void setMatrix4(int port, const glm::mat4 &mat);
				void setFloat4(int port, float a, float b, float c, float d);
				void setColor(const gfx::Color &color);
				
				void clear(const gfx::Color &color = gfx::color::White);
				
				gfx::Shader* createShader(const gfx::ShaderSource &shaderSource);
				void destroy(gfx::Shader *shader);
				
				void setShader(gfx::Shader *shader);
				void setShader(gfx::Shader *shader, const gfx::Color &color);
				void setShader(gfx::Shader *shader, const glm::mat4 &projection, const glm::mat4 &view);
				void setShader(gfx::Shader *shader, const glm::mat4 &projection, const glm::mat4 &view, const gfx::Color &color);
				
				// Renderer
				gfx::Texture2D* createTexture2D(gfx::Image *image);
				
				void bindTexture(gfx::Texture2D *texture);
				
				void draw(gfx::Texture2D *texture);
				
				void draw(gfx::Texture2D *texture, gfx::Rectangle target);
				
				void draw(gfx::Texture2D *texture, gfx::Rectangle origin, gfx::Rectangle target);
				
				void destroy(gfx::Texture2D *texture);
				
				gfx::ModelMesh* createModelMesh(gfx::Mesh *mesh);
				
				void draw(gfx::ModelMesh *model);
				
				void destroy(gfx::ModelMesh *model);
				
				template<class T>
				T* load(const std::string &filename)
				{
					return _content->load<T>(filename);
				}
				
				template<class T>
				void save(const std::string &filename, const T *resource)
				{
					_content->save<T>(filename, resource);
				}
				
				gfx::ModelMesh* loadSphere(float radius, int lat, int lon);
				gfx::Texture2D* loadTexture(const std::string &filename);
				gfx::Shader* loadShader(const std::string &vertexFile, const std::string &fragmentFile);
			
			private:
				
				gfx::Display *_display;
				gfx::Context *_context;
				gfx::Renderer *_renderer;
				Content *_content;
			
		};
	}
}

#endif
