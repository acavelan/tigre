#include <QtWidgets>

#include "QT5Window.hpp"
#include "QT5Display.hpp"


QT5Window::QT5Window()
{        
	QT5Display *display = new QT5Display();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(display);
    setLayout(mainLayout);

    setWindowTitle(tr("Tigre"));
}

void QT5Window::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        close();
    else
        QWidget::keyPressEvent(e);
}
