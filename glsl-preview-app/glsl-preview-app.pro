TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

TARGET = "GLSL Preview"
ICON = "glsl-preview.icns"

SOURCES += main.cpp \
    glview/glviewport.cpp \
    glview/glviewrenderer.cpp \
    glview/renderables/quad.cpp \
    glview/shaderuniformlist.cpp \
    glview/shaderuniform.cpp \
    glview/shaders/shaderlibrary.cpp \
    glview/renderables/cube.cpp \
    glview/ucache/vecuniformcache.cpp \
    glview/ucache/sampler2duniformcache.cpp \
    glview/obj_loader.c \
    glview/renderables/objmodel.cpp \
    glview/logger.cpp \
    glview/texturecache.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += glm
INCLUDEPATH += /usr/local/Cellar/freeimage/3.17.0/include

LIBS += -L/usr/local/Cellar/freeimage/3.17.0/lib -lfreeimage

HEADERS += \
    glview/glviewport.h \
    glview/glviewrenderer.h \
    glview/renderables/renderable.h \
    glview/renderables/quad.h \
    glview/shaderuniformlist.h \
    glview/shaderuniform.h \
    glview/vecuniformcache.h \
    glview/uniformcache.h \
    glview/shaders/shaderlibrary.h \
    glview/renderables/cube.h \
    glview/ucache/uniformcache.h \
    glview/ucache/vecuniformcache.h \
    glview/ucache/sampler2duniformcache.h \
    glview/obj_loader.h \
    glview/renderables/objmodel.h \
    glview/logger.h \
    glview/texturecache.h
