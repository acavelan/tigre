#include "QT5DisplayWidget.hpp"

using namespace core;
using namespace gfx;

QT5DisplayWidget::QT5DisplayWidget(QWidget *parent) : 
	QGLWidget(QGLFormat(desiredFormat()), parent)
{
}

QT5DisplayWidget::~QT5DisplayWidget() 
{
	delete _app;
	delete _content;
	delete _renderer;
	delete _context;
}

QGLFormat QT5DisplayWidget::desiredFormat()
{
    QGLFormat fmt(QGL::SampleBuffers);
    fmt.setSwapInterval(1);
    return fmt;
}

void QT5DisplayWidget::resize(int width, int height)
{
	_width = width;
	_height = height;
	
	QGLWidget::resize(width, height);
}

int QT5DisplayWidget::getWidth() const
{
	return _width;
}

int QT5DisplayWidget::getHeight() const
{
	return _height;
}

void QT5DisplayWidget::initializeGL()
{
	makeCurrent();
	
	_logger = new ConsoleLogger("Application");
	
	_context = new OpenGLContext(this);
	_renderer = new OpenGLRenderer(_context); 

	_context->init();
	_renderer->init();
	
	_context->printGLString(GL_VENDOR, _logger);
	_context->printGLString(GL_RENDERER, _logger);
	_context->printGLString(GL_VERSION, _logger);
	_context->printGLString(GL_SHADING_LANGUAGE_VERSION, _logger);
	
	_content = new Content();
	_content->registerLoader(new ImageLoader(), "jpg,bmp,png,tga");
	
	_app = new Application(this, _context, _renderer, _content, _logger);
	
    connect(&refresh, SIGNAL(timeout()), this, SLOT(updateGL()));
	refresh.setInterval(0);
    refresh.start();
    
    timer.start();
}

void QT5DisplayWidget::paintGL()
{
	_app->update(timer.tick());
	_app->drawFrame();
}

void QT5DisplayWidget::resizeGL(int width, int height)
{
	_width = width;
	_height = height;
	
	_app->resize(width, height);
}
