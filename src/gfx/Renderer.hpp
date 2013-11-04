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

#ifndef RENDERER_H
#define RENDERER_H

#include "Mesh.hpp"
#include "Image.hpp"
#include "Texture2D.hpp"
#include "ModelMesh.hpp"
#include "Rectangle.hpp"

namespace tigre
{
	namespace gfx
	{
		class Renderer
		{
			public:
				
				virtual ~Renderer() {}
				
				virtual void init() = 0;
				
				virtual void destroy() = 0;
				
				// Texture
				virtual Texture2D* createTexture2D(Image *image) = 0;
				
				virtual void bindTexture(Texture2D *texture) = 0;
				
				virtual void draw(Texture2D *texture) = 0;
				
				virtual void draw(Texture2D *texture, Rectangle target) = 0;
				
				virtual void draw(Texture2D *texture, Rectangle origin, Rectangle target) = 0;
				
				virtual void destroy(Texture2D *texture) = 0;
				
				// Mesh
				virtual ModelMesh* createModelMesh(Mesh *mesh) = 0;
				
				virtual void draw(ModelMesh *model) = 0;
				
				virtual void destroy(ModelMesh *model) = 0;
		};
	}
}

#endif
