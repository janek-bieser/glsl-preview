TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

TARGET = "GLSL Preview"

SOURCES += main.cpp \
    glview/glviewport.cpp \
    glview/glviewrenderer.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    glview/glviewport.h \
    glview/glviewrenderer.h
