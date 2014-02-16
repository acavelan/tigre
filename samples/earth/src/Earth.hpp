#ifndef EARTH_H
#define EARTH_H

#include "core/core.hpp"
#include "game/game.hpp"
#include "gfx/gfx.hpp"

using namespace tigre::core;
using namespace tigre::game;
using namespace tigre::gfx;

using namespace glm;

class Earth : public Game
{
    public:

        Earth(Display *display,
                    Context *context,
                    Renderer *renderer,
                    Content *content,
                    Logger *logger);

        ~Earth();

        void start();

        void stop();

        void resize(int width, int height);

        void update(float delta);

        void drawFrame();

    private:

        Logger *_log;

        Texture2D *_earthTex, *_whiteTex;
        ModelMesh *_sphere;
        Shader *_shader;

        mat4 _projection, _projection2D;
        mat4 _view, _view2D;

        float _angle;

};

#endif
