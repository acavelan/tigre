#ifndef RENDERVIEW_H
#define RENDERVIEW_H

#include "../gfx/Display.hpp"
#include "../gfx/Context.hpp"
#include "../gfx/Renderer.hpp"

namespace tigre
{
    namespace hl
    {
        class RenderView : public gfx::Display,
            public gfx::Context,
            public gfx::Renderer
        {
            public:

                RenderView(gfx::Display *display, gfx::Context *context, gfx::Renderer *renderer);

                virtual ~RenderView();

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

                // RenderView
                gfx::Texture2D* createTexture2D(gfx::Image *image);

                void bindTexture(gfx::Texture2D *texture);

                void draw(gfx::Texture2D *texture);

                void draw(gfx::Texture2D *texture, gfx::Rectangle target);

                void draw(gfx::Texture2D *texture, gfx::Rectangle origin, gfx::Rectangle target);

                void destroy(gfx::Texture2D *texture);

                gfx::ModelMesh* createModelMesh(gfx::Mesh *mesh);

                void draw(gfx::ModelMesh *model);

                void destroy(gfx::ModelMesh *model);

            private:

                gfx::Display *_display;
                gfx::Context *_context;
                gfx::Renderer *_renderer;

        };
    }
}

#endif
