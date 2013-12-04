#ifndef MESH_H
#define MESH_H

#include "../core/Resource.hpp"

namespace tigre
{
    namespace gfx
    {
        class Mesh : public core::Resource
        {
            public:

                Mesh();

                virtual ~Mesh();

                float *vertices, *normals, *texCoords;

                unsigned int *indices;

                unsigned int vertexCount, normalCount, texCoordCount, indexCount;
        };
    }
}

#endif
