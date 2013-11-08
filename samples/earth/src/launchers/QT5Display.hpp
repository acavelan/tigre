#ifndef QT5DISPLAY_H
#define QT5DISPLAY_H

#include <QGLWidget>
#include <QTimer>

#include "user/core.hpp"
#include "user/gfx.hpp"

#include "core/Logger/ConsoleLogger.hpp"
#include "gfx/Display/GLFWDisplay.hpp"
#include "gfx/Context/OpenGLContext.hpp"
#include "gfx/Renderer/OpenGLRenderer.hpp"

#include "Content.hpp"
#include "Application.hpp"

using namespace tigre;

class QT5Display : public QGLWidget, public gfx::Display
{
    Q_OBJECT

	public:
	
		QT5Display(QWidget *parent = 0);

		virtual ~QT5Display();
		
		QGLFormat desiredFormat();
		
		void setApplication(Application *app);
		
		bool valid() const;
		
		void resize(int width, int height);
		
		int getWidth() const;

		int getHeight() const;
	
	protected:
	
		void initializeGL();
		
		void paintGL();
		
		void resizeGL(int width, int height);

	private:
	
		core::ConsoleLogger *_logger;
		gfx::OpenGLContext *_context;
		gfx::OpenGLRenderer *_renderer; 
		
		Content *_content;
		Application *_app;
		
		QTimer refresh;
		core::Timer timer;
		
		int _width, _height;
		bool _valid;

};

#endif
