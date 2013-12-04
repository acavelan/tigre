#include "Mesh.hpp"

namespace tigre
{
    namespace gfx
    {
        Mesh::Mesh() :
            vertices(0), normals(0), texCoords(0), indices(0),
            vertexCount(0), normalCount(0), texCoordCount(0), indexCount(0)
        {
        }

        Mesh::~Mesh()
        {
            if(vertices) delete[] vertices;
            if(normals) delete[] normals;
            if(texCoords) delete[] texCoords;
            if(indices) delete[] indices;
        }
    }
}
