#include <QApplication>

#include "QT5Window.hpp"
#include "user/core.hpp"

int main(int argc, char **argv)
{	
	int width = 800;
	int height = 600;
        
	if(argc > 2)
	{
		width = tigre::core::toInt(argv[1]);
		height = tigre::core::toInt(argv[2]);
	}
	
	QApplication app(argc, argv);
	
    QT5Window window;
	window.resize(width, height);
    window.show();
        
    return app.exec();
}
