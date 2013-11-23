#ifndef APPLICATION_H
#define APPLICATION_H

#include "core/core.hpp"
#include "gfx/gfx.hpp"

#include "Content.hpp"

using namespace glm;
using namespace tigre::core;
using namespace tigre::gfx;

class Application
{
    public:

        Application(Display *display, Context *context, Renderer *renderer, core::Logger *logger, Content *content);
					
        ~Application();

        void init();
        
        void destroy();
        
        void resize(int width, int height);
        
        void update(float delta);

        void drawFrame();
        
        ModelMesh* loadSphere(float radius, int lat, int lon);
        Texture2D* loadTexture(const std::string &filename);
        Shader* loadShader(const std::string &vertexFile, const std::string &fragmentFile);

    private:
		
        Display *_display;
        Context *_context;
        Renderer *_renderer;
        
        Logger *_log;
        Content *_content;
        
        Texture2D *_earthTex, *_whiteTex;
        ModelMesh *_sphere;
        Shader *_shader;
		
		int _width, _height;
		
		float _angle;
        
        mat4 _projection, _projection2D;
        mat4 _view, _view2D;
        
};

#endif
