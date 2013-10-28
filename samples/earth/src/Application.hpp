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

class Application
{
    public:

        Application(tigre::utils::Logger *log,
					tigre::graphics::Display *display, 
					tigre::graphics::Context *context,
					tigre::graphics::Renderer *renderer);
					
        ~Application();

        void init();
        
        void destroy();
        
        void resize(int width, int height);
        
        void update(float delta);

        void drawFrame();

    private:
		
		tigre::utils::Logger *_log;
        tigre::graphics::Display *_display;
        tigre::graphics::Context *_context;
        tigre::graphics::Renderer *_renderer;
        
        tigre::graphics::Texture2D *_earthTex, *_whiteTex;
        tigre::graphics::ModelMesh *_sphere;
        tigre::graphics::Shader *_shader;
		
		int _width, _height;
		
		int _FPS;
		
		float _timer;
		
		float _angle;
        
        // Camera
        glm::mat4 _projMat, _projMat2D;
        glm::mat4 _viewMat, _viewMat2D;
        glm::mat4 _modelMat;
        
};

#endif
