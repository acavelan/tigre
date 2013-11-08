TARGET = qt

CONFIG += qt
QT += opengl widgets

tigre = ../../../..
tigresrc = $$tigre/src

root = ../..
rootsrc = $$root/src

SOURCES += 	$$rootsrc/launchers/qt.cpp \
			$$rootsrc/launchers/QT5Display.cpp \
			$$rootsrc/launchers/QT5Window.cpp \
			$$rootsrc/Application.cpp \
			$$rootsrc/Sphere.cpp

HEADERS += 	$$rootsrc/launchers/QT5Display.hpp \
			$$rootsrc/launchers/QT5Window.hpp \
			$$rootsrc/Application.hpp \
			$$rootsrc/Content.hpp \
			$$rootsrc/Sphere.hpp

INCLUDEPATH += 	$$tigre/local \
				$$tigresrc \
				$$rootsrc

LIBS += -L. -ltigre
