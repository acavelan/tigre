#ifndef APPLICATION_H
#define APPLICATION_H

#include "user/core.hpp"
#include "user/graphics.hpp"

#include "Content.hpp"

using namespace tigre;

class Application
{
    public:

        Application(graphics::Display *display, 
					graphics::Context *context,
					graphics::Renderer *renderer,
					core::Logger *logger,
					Content *content);
					
        ~Application();

        void init();
        
        void destroy();
        
        void resize(int width, int height);
        
        void update(float delta);

        void drawFrame();

    private:
		
        graphics::Display *_display;
        graphics::Context *_context;
        graphics::Renderer *_renderer;
        
        core::Logger *_log;
        Content *_content;
        
        graphics::Texture2D *_earthTex, *_whiteTex;
        graphics::ModelMesh *_sphere;
        graphics::Shader *_shader;
		
		int _width, _height;
		
		int _FPS;
		
		float _timer;
		
		float _angle;
        
        // World
        glm::mat4 _projection, _projection2D;
        glm::mat4 _view, _view2D;
        
};

#endif
