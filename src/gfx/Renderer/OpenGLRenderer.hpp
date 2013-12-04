#ifndef OPENGL_RENDERER_H
#define OPENGL_RENDERER_H

#include <vector>

#include "../Renderer.hpp"
#include "../Context/OpenGLContext.hpp"

namespace tigre
{
    namespace gfx
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

                // Texture
                Texture2D* createTexture2D(Image *image);

                void bindTexture(Texture2D *texture);

                void draw(Texture2D *texture);

                void draw(Texture2D *texture, Rectangle target);

                void draw(Texture2D *texture, Rectangle origin, Rectangle target);

                void destroy(Texture2D *texture);

                // Mesh
                ModelMesh* createModelMesh(Mesh *mesh);

                void draw(ModelMesh *model);

                void destroy(ModelMesh *model);

            private:

                OpenGLContext *_context;

                OpenGLQuad _quad;

                std::vector<OpenGLTexture*> _glTextures;
                std::vector<OpenGLModelMesh*> _glModels;

        };
    }
}

#endif
