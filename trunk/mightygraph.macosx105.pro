TEMPLATE = app
DEPENDPATH += . build src ui
INCLUDEPATH += . /usr/local/include
QT = gui core xml svg
CONFIG += qt \
 warn_on \
 console \
 x86 \
 debug_and_release
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build
UI_DIR = build
FORMS = ui/mainwindow.ui ui/preferences.ui
HEADERS = src/mainwindowimpl.h \
 src/svggraph.h \
 src/transform.h \
 src/preferencesimpl.h \
 src/scroll.h \
 src/preview.h
SOURCES = src/mainwindowimpl.cpp \
 src/main.cpp \
 src/svggraph.cpp \
 src/transform.cpp \
 src/preferencesimpl.cpp \
 src/scroll.cpp \
 src/preview.cpp
RESOURCES = ui/ressources.qrc
ICON = theapp.icns
LIBS += -lxml2 -lxslt
