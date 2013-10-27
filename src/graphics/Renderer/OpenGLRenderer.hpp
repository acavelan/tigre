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

#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <vector>

#include "../Renderer.hpp"
#include "../Context/OpenGLContext.hpp"

namespace tigre
{
	namespace graphics
	{	
		class OpenGLTexture
		{
			public:
				
				GLuint textureId;
		};
		
		class OpenGLModelMesh
		{
			public:
				
				GLuint vbo[4];
		};
		
		class OpenGLQuad
		{
			public:
				
				GLuint vbo[3];
		};
		
		class OpenGLRenderer : public Renderer
		{
			public:
			
				OpenGLRenderer(OpenGLContext *context);
				
				~OpenGLRenderer();
				
				void init();
				
				void destroy();
				
				void load(Texture2D *texture);
				
				void unload(Texture2D *texture);
				
				void bindTexture(Texture2D *texture);
				
				void load(ModelMesh *model);
				
				void unload(ModelMesh *model);
				
				void draw(ModelMesh *model);
				
				void draw(Texture2D *texture);
				
				void draw(Texture2D *texture, Rectangle target);
				
				void draw(Texture2D *texture, Rectangle origin, Rectangle target);
			
			private:
				
				OpenGLContext *_context;
				
				OpenGLQuad _quad;
				std::vector<OpenGLTexture*> _glTextures;
				std::vector<OpenGLModelMesh*> _glModels;

		};
	}
}

#endif
