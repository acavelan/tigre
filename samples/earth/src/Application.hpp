#ifndef APPLICATION_H
#define APPLICATION_H

#include "user/core.hpp"
#include "user/gfx.hpp"

#include "Content.hpp"

using namespace tigre;

class Application
{
    public:

        Application(gfx::Display *display, 
					gfx::Context *context,
					gfx::Renderer *renderer,
					core::Logger *logger,
					Content *content);
					
        ~Application();

        void init();
        
        void destroy();
        
        void resize(int width, int height);
        
        void update(float delta);

        void drawFrame();

    private:
		
        gfx::Display *_display;
        gfx::Context *_context;
        gfx::Renderer *_renderer;
        
        core::Logger *_log;
        Content *_content;
        
        gfx::Texture2D *_earthTex, *_whiteTex;
        gfx::ModelMesh *_sphere;
        gfx::Shader *_shader;
		
		int _width, _height;
		
		int _FPS;
		
		float _timer;
		
		float _angle;
        
        // World
        glm::mat4 _projection, _projection2D;
        glm::mat4 _view, _view2D;
        
};

#endif
