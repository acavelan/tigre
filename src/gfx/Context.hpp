#ifndef CONTEXT_H
#define CONTEXT_H

#include <glm/glm.hpp>

#include "Color.hpp"
#include "Shader.hpp"

/**
 * An OpenGL context represents many things. A context stores all of the state
 * associated with this instance of OpenGL. It represents the (potentially
 * visible) default framebuffer that rendering commands will draw to when not
 * drawing to a framebuffer object. Think of a context as an object that holds
 * all of OpenGL; when a context is destroyed, OpenGL is destroyed.
 */
namespace tigre
{
    namespace gfx
    {
        class Context
        {
            public:

                virtual ~Context() {}

                virtual void setViewport(int x, int y, int width, int height) = 0;
                virtual void setViewport(int width, int height) = 0;

                virtual int getViewPortX() const = 0;
                virtual int getViewPortY() const = 0;

                virtual int getViewPortWidth() const = 0;
                virtual int getViewPortHeight() const = 0;

                virtual void setMatrix4(int port, const glm::mat4 &mat) = 0;
                virtual void setFloat4(int port, float a, float b, float c, float d) = 0;

                virtual void clear(const Color &color = color::White) = 0;

                virtual Shader* createShader(const ShaderSource &shaderSource) = 0;
                virtual void destroy(Shader *shader) = 0;

                virtual void setShader(Shader *shader) = 0;
        };
    }
}

#endif
