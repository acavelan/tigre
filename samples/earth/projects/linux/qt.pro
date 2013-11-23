TARGET = qt

CONFIG += qt
QT += opengl widgets

tigre = ../../../..
tigresrc = $$tigre/src

root = ../..
rootsrc = $$root/src

SOURCES += 	$$rootsrc/launchers/qt/main.cpp \
			$$rootsrc/launchers/qt/QT5Window.cpp \
			$$rootsrc/launchers/qt/QT5DisplayWidget.cpp \
			$$rootsrc/Application.cpp \
			$$rootsrc/Sphere.cpp

HEADERS += 	$$rootsrc/launchers/qt/QT5DisplayWidget.hpp \
			$$rootsrc/launchers/qt/QT5Window.hpp \
			$$rootsrc/Application.hpp \
			$$rootsrc/Content.hpp \
			$$rootsrc/Sphere.hpp

INCLUDEPATH += 	$$tigre/local \
				$$tigresrc \
				$$rootsrc

LIBS += -L. -ltigre
