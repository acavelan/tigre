#ifndef EARTH_H
#define EARTH_H

#include "core/core.hpp"
#include "gfx/gfx.hpp"
#include "hl/hl.hpp"

using namespace tigre::core;
using namespace tigre::gfx;
using namespace tigre::hl;

using namespace glm;

class Earth
{
    public:

        Earth(RenderView *renderer, Content *content, Logger *logger);

        ~Earth();

        void resize(int width, int height);

        void update(float delta);

        void render();

    private:

        ModelMesh* loadSphere(float radius, int lat, int lon);

        Texture2D* loadTexture(const std::string &filename);

        Shader* loadShader(const std::string &vertexFile, const std::string &fragmentFile);

    private:

        RenderView *_rdr;
        Content *_content;
        Logger *_log;

        Texture2D *_earthTex;
        ModelMesh *_sphere;
        Shader *_shader;

        mat4 _projection, _projection2D;
        mat4 _view, _view2D;

        float _angle;
};

#endif
