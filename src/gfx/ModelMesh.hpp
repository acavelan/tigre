#ifndef MODELMESH_H
#define MODELMESH_H

#include "../core/Resource.hpp"

namespace tigre
{
    namespace gfx
    {
        class ModelMesh : public core::Resource
        {
            public:

                ModelMesh();

                virtual ~ModelMesh();

                int token;

                unsigned int vertexCount;
                unsigned int normalCount;
                unsigned int texCoordCount;
                unsigned int indexCount;

        };
    }
}

#endif
