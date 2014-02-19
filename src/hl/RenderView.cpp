#include "RenderView.hpp"

namespace tigre
{
    namespace hl
    {
        RenderView::RenderView(gfx::Display *display, gfx::Context *context, gfx::Renderer *renderer) :
            _display(display), _context(context), _renderer(renderer)
        {
        }

        RenderView::~RenderView()
        {
        }

        void RenderView::resize(int width, int height)
        {
            _display->resize(width, height);
        }

        int RenderView::getWidth() const
        {
            return _display->getWidth();
        }

        int RenderView::getHeight() const
        {
            return _display->getHeight();
        }

        void RenderView::setViewport(int x, int y, int width, int height)
        {
            _context->setViewport(x, y, width, height);
        }

        void RenderView::setViewport(int width, int height)
        {
            _context->setViewport(width, height);
        }

        int RenderView::getViewPortX() const
        {
            return _context->getViewPortX();
        }

        int RenderView::getViewPortY() const
        {
            return _context->getViewPortY();
        }

        int RenderView::getViewPortWidth() const
        {
            return _context->getViewPortWidth();
        }

        int RenderView::getViewPortHeight() const
        {
            return _context->getViewPortHeight();
        }

        void RenderView::setMatrix4(int port, const glm::mat4 &mat)
        {
            _context->setMatrix4(port, mat);
        }

        void RenderView::setFloat4(int port, float a, float b, float c, float d)
        {
            _context->setFloat4(port, a, b, c, d);
        }

        void RenderView::setColor(const gfx::Color &color)
        {
            _context->setFloat4(gfx::shader::color, color.r, color.g, color.b, color.a);
        }

        void RenderView::clear(const gfx::Color &color)
        {
            _context->clear(color);
        }

        gfx::Shader* RenderView::createShader(const gfx::ShaderSource &shaderSource)
        {
            return _context->createShader(shaderSource);
        }

        void RenderView::destroy(gfx::Shader *shader)
        {
            _context->destroy(shader);
        }

        void RenderView::setShader(gfx::Shader *shader)
        {
            _context->setShader(shader);
        }

        void RenderView::setShader(gfx::Shader *shader, const gfx::Color &color)
        {
            _context->setShader(shader);
            _context->setFloat4(gfx::shader::color, color.r, color.g, color.b, color.a);
        }

        void RenderView::setShader(gfx::Shader *shader, const glm::mat4 &projection, const glm::mat4 &view)
        {
            _context->setShader(shader);
            _context->setMatrix4(gfx::shader::projection, projection);
            _context->setMatrix4(gfx::shader::view, view);
        }

        void RenderView::setShader(gfx::Shader *shader, const glm::mat4 &projection, const glm::mat4 &view, const gfx::Color &color)
        {
            _context->setShader(shader);
            _context->setMatrix4(gfx::shader::projection, projection);
            _context->setMatrix4(gfx::shader::view, view);
            _context->setFloat4(gfx::shader::color, color.r, color.g, color.b, color.a);
        }

        gfx::Texture2D* RenderView::createTexture2D(gfx::Image *image)
        {
            return _renderer->createTexture2D(image);
        }

        void RenderView::bindTexture(gfx::Texture2D *texture)
        {
            _renderer->bindTexture(texture);
        }

        void RenderView::draw(gfx::Texture2D *texture)
        {
            _renderer->draw(texture);
        }

        void RenderView::draw(gfx::Texture2D *texture, gfx::Rectangle target)
        {
            _renderer->draw(texture, target);
        }

        void RenderView::draw(gfx::Texture2D *texture, gfx::Rectangle origin, gfx::Rectangle target)
        {
            _renderer->draw(texture, origin, target);
        }

        void RenderView::destroy(gfx::Texture2D *texture)
        {
            _renderer->destroy(texture);
        }

        gfx::ModelMesh* RenderView::createModelMesh(gfx::Mesh *mesh)
        {
            return _renderer->createModelMesh(mesh);
        }

        void RenderView::draw(gfx::ModelMesh *model)
        {
            _renderer->draw(model);
        }

        void RenderView::destroy(gfx::ModelMesh *model)
        {
            _renderer->destroy(model);
        }
    }
}
