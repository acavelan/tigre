#ifndef APPLICATION_H
#define APPLICATION_H

#include "utils/Timer.hpp"
#include "utils/Logger.hpp"

#include "graphics/Display.hpp"
#include "graphics/Context.hpp"
#include "graphics/Renderer.hpp"
#include "graphics/Shader.hpp"
#include "graphics/ModelMesh.hpp"
#include "graphics/Color.hpp"
#include "graphics/Texture2D.hpp"

#include "kit/Content.hpp"

using namespace glm;
using namespace tigre;

class Application
{
    public:

        Application(utils::Logger *log,
					graphics::Display *display, 
					graphics::Context *context,
					graphics::Renderer *renderer,
					kit::Content *content);
					
        ~Application();

        void init();
        
        void destroy();
        
        void resize(int width, int height);
        
        void update(float delta);

        void drawFrame();

    private:
		
		utils::Logger *_log;
        graphics::Display *_display;
        graphics::Context *_context;
        graphics::Renderer *_renderer;
        
        kit::Content *_content;
        
        graphics::Texture2D *_earthTex, *_whiteTex;
        graphics::ModelMesh *_sphere;
        graphics::Shader *_shader;
		
		int _width, _height;
		
		int _FPS;
		
		float _timer;
		
		float _angle;
        
        // World
        mat4 _projection, _projection2D;
        mat4 _view, _view2D;
        
};

#endif
