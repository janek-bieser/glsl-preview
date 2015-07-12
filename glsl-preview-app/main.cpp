#include <QApplication>
#include <QQmlApplicationEngine>
#include <QSurfaceFormat>
#include <QQuickWindow>

#include "glview/glviewport.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<GLViewport>("GLRendering", 1, 0, "GLViewport");

    QSurfaceFormat format;
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    qDebug() << window->title();
    window->setFormat(format);

    window->show();

    return app.exec();
}
