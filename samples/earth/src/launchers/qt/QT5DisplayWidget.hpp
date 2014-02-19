#ifndef QT5DISPLAYWIDGET_H
#define QT5DISPLAYWIDGET_H

#include <QGLWidget>
#include <QTimer>

#include "core/core.hpp"
#include "gfx/gfx.hpp"

#include "core/Logger/ConsoleLogger.hpp"
#include "gfx/Display/GLFWDisplay.hpp"
#include "gfx/Context/OpenGLContext.hpp"
#include "gfx/Renderer/OpenGLRenderer.hpp"

#include "Earth.hpp"

using namespace tigre;

class QT5DisplayWidget : public QGLWidget, public gfx::Display
{
        Q_OBJECT

    public:

        QT5DisplayWidget(QWidget *parent = 0);

        virtual ~QT5DisplayWidget();

        QGLFormat desiredFormat();

        void resize(int width, int height);

        int getWidth() const;

        int getHeight() const;

    protected:

        void initializeGL();

        void paintGL();

        void resizeGL(int width, int height);

    private:

        core::ConsoleLogger *_log;
        gfx::OpenGLContext *_context;
        gfx::OpenGLRenderer *_renderer;
        hl::RenderView *_renderView;

        Content *_content;
        Earth *_app;

        QTimer refresh;
        core::Timer timer;

        int _width, _height;

};

#endif
