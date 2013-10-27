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

#ifndef MESH_H
#define MESH_H

#include "../core/Resource.hpp"

namespace tigre
{
	namespace graphics
	{
		class Mesh : public core::Resource
		{
			public:
				
				Mesh();
				virtual ~Mesh();
				
				void destroy();
				
				void setVertices(float *vertices, unsigned int vertexCount);
				void setNormals(float *normals, unsigned int normalCount);
				void setTexCoords(float *texCoords, unsigned int texCoordCount);
				void setIndices(unsigned int *indices, unsigned int indexCount);
				
				unsigned int getVertexCount() const;
				unsigned int getNormalCount() const;
				unsigned int getTexCoordCount() const;
				unsigned int getIndexCount() const;

				float *getVertices() const;
				float *getNormals() const;
				float *getTexCoords() const;
				unsigned int *getIndices() const;
			
			protected:
				
				float *_vertices, *_normals, *_texCoords;
				
				unsigned int *_indices;

				unsigned int _vertexCount, _normalCount, _texCoordCount, _indexCount;
		};
	}
}

#endif
