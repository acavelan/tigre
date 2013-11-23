#ifndef QT5QT5WINDOW_H
#define QT5QT5WINDOW_H

#include <QWidget>

class QT5Window : public QWidget
{
    Q_OBJECT

	public:
	
		QT5Window();

	protected:
	
		void keyPressEvent(QKeyEvent *event);
		
};

#endif
