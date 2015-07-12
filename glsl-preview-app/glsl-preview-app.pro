TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

TARGET = "GLSL Preview"

SOURCES += main.cpp \
    glview/glviewport.cpp \
    glview/glviewrenderer.cpp \
    glview/renderables/quad.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

INCLUDEPATH += glm

HEADERS += \
    glview/glviewport.h \
    glview/glviewrenderer.h \
    glview/renderables/renderable.h \
    glview/renderables/quad.h
