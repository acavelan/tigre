#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/core.hpp"
#include "game/game.hpp"
#include "gfx/gfx.hpp"

using namespace glm;
using namespace tigre::core;
using namespace tigre::game;
using namespace tigre::gfx;

class Application : public Game
{
    public:

        Application(Display *display, Context *context, Renderer *renderer, Content *content, Logger *logger);
					
        ~Application();
        
        void resize(int width, int height);
        
        void update(float delta);

        void drawFrame();

    private:
		
        Logger *_log;
        
        Texture2D *_earthTex, *_whiteTex;
        ModelMesh *_sphere;
        Shader *_shader;
		
		float _angle;
        
        mat4 _projection, _projection2D;
        mat4 _view, _view2D;
        
};

#endif
