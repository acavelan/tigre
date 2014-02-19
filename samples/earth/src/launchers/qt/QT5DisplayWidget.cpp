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
    delete _renderView;
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

    _log = new ConsoleLogger("Tigre");

    try
    {
        _context = new OpenGLContext();
        _renderer = new OpenGLRenderer(_context);

        _context->printGLString(GL_VENDOR, _log);
        _context->printGLString(GL_RENDERER, _log);
        _context->printGLString(GL_VERSION, _log);
        _context->printGLString(GL_SHADING_LANGUAGE_VERSION, _log);

        _content = new Content();
        _content->addLocation("content", "../../content");
        _content->addLocation("shaders", "../../content/shaders/130");
        _content->registerLoader(new ImageLoader(), "jpg,bmp,png,tga");

        _renderView =  new RenderView(this, _context, _renderer);

        _app = new Earth(_renderView, _content, _log);

        connect(&refresh, SIGNAL(timeout()), this, SLOT(updateGL()));
        refresh.setInterval(0);
        refresh.start();

        timer.start();
    }
    catch(const Exception &e)
    {
        _log->error(e.what());
    }
}

void QT5DisplayWidget::paintGL()
{
    _app->update(timer.tick());
    _app->render();
    _context->checkGlError("app.render()", _log);
}

void QT5DisplayWidget::resizeGL(int width, int height)
{
    _width = width;
    _height = height;

    _app->resize(width, height);
}
