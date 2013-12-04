#ifndef OPENGL_CONTEXT_H
#define OPENGL_CONTEXT_H

#include <vector>

#include "../Context.hpp"
#include "../../core/Logger.hpp"
#include "../../core/os.hpp"

#if defined(OS_LINUX)
#include <GL/gl.h>
#include <GL/glext.h>
#elif defined(OS_ANDROID)
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#endif

namespace tigre
{
    namespace gfx
    {
        class OpenGLShader
        {
            public:

                GLint program;
                GLint ports[shader::count];
        };

        class OpenGLContext : public Context
        {
            public:

                OpenGLContext();
                ~OpenGLContext();

                void init();
                void destroy();

                void printGLString(GLenum s, const core::Logger *log);
                void checkGlError(const char* op, const core::Logger *log);

                void setViewport(int x, int y, int width, int height);
                void setViewport(int width, int height);

                int getViewPortX() const;
                int getViewPortY() const;

                int getViewPortWidth() const;
                int getViewPortHeight() const;

                void setMatrix4(int port, const glm::mat4 &mat);

                void setFloat4(int port, float a, float b, float c, float d);

                void clear(const Color &color);

                Shader* createShader(const ShaderSource &shaderSource);
                void destroy(Shader *shader);

                void setShader(Shader *shader);

                OpenGLShader *getCurrentShader();

            private:

                GLuint createShader(GLenum shaderType, const char *source);
                GLuint createShaderProgram(GLuint vertexShader, GLuint fragmentShader);

                OpenGLShader *_shader;
                std::vector<OpenGLShader*> _glShaders;

                int _x, _y;
                int _width, _height;

        };
    }
}

#endif
