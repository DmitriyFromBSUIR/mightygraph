TEMPLATE = app
DEPENDPATH += . build src ui
INCLUDEPATH += .
QT = gui core xml svg
CONFIG += qt \
 warn_on \
 console \
 x86 \
 release
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui
HEADERS = src/mainwindowimpl.h src/svggraph.h src/transform.h
SOURCES = src/mainwindowimpl.cpp src/main.cpp src/svggraph.cpp src/transform.cpp
ICON = theapp.icns
