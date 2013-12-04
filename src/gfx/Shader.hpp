#ifndef SHADER_H
#define SHADER_H

#include <string>

#include "../core/Resource.hpp"

namespace tigre
{
    namespace gfx
    {
        namespace shader
        {
            // Uniforms
            const int projection = 0;
            const int model = 1;
            const int view = 2;
            const int color = 3;

            // Attributes
            const int position = 4;
            const int normal = 5;
            const int texCoord = 6;
            const int texture0 = 7;

            const int count = 8;
        }

        class ShaderSource : public core::Resource
        {
            public:

                virtual ~ShaderSource() {}

                std::string vertexShader;
                std::string fragmentShader;
        };

        class Shader : public core::Resource
        {
            public:

                Shader();

                virtual ~Shader();

                int token;
        };
    }
}

#endif
