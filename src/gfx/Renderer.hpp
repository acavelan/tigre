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
