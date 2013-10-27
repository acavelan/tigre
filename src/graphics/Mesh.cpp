#include "Mesh.hpp"

namespace tigre
{
	namespace graphics
	{
		Mesh::Mesh() : 
			_vertices(0), _normals(0), _texCoords(0), _indices(0),
			_vertexCount(0), _normalCount(0), _texCoordCount(0), _indexCount(0)
		{
		}

		Mesh::~Mesh()
		{
			if(_vertices) delete[] _vertices;
			if(_normals) delete[] _normals;
			if(_texCoords) delete[] _texCoords;
			if(_indices) delete[] _indices;
		}
				
		void Mesh::setVertices(float *vertices, unsigned int vertexCount)
		{
			_vertices = vertices;
			_vertexCount = vertexCount;
		}

		void Mesh::setNormals(float *normals, unsigned int normalCount)
		{
			_normals = normals;
			_normalCount = normalCount;
		}

		void Mesh::setTexCoords(float *texCoords, unsigned int texCoordCount)
		{
			_texCoords = texCoords;
			_texCoordCount = texCoordCount;
		}

		void Mesh::setIndices(unsigned int *indices, unsigned int indexCount)
		{
			_indices = indices;
			_indexCount = indexCount;
		}

		unsigned int Mesh::getVertexCount() const
		{
			return _vertexCount;
		}

		unsigned int Mesh::getNormalCount() const
		{
			return _normalCount;
		}

		unsigned int Mesh::getTexCoordCount() const
		{
			return _texCoordCount;
		}

		unsigned int Mesh::getIndexCount() const
		{
			return _indexCount;
		}

		float *Mesh::getVertices() const
		{
			return _vertices;
		}

		float *Mesh::getNormals() const
		{
			return _normals;
		}

		float *Mesh::getTexCoords() const
		{
			return _texCoords;
		}

		unsigned int *Mesh::getIndices() const
		{
			return _indices;
		}
	}
}
