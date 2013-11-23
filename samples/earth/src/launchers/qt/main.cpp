#include <QApplication>

#include "QT5Window.hpp"
#include "core/core.hpp"

using namespace tigre::core;

int main(int argc, char **argv)
{	
	int width = 800;
	int height = 600;
        
	if(argc > 2)
	{
		width = toInt(argv[1]);
		height = toInt(argv[2]);
	}
	
	QApplication app(argc, argv);
	
    QT5Window window;
	window.resize(width, height);
    window.show();
        
    return app.exec();
}
