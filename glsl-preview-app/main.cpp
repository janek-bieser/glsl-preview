#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QSurfaceFormat>
#include <QQuickWindow>

#include "glview/glviewport.h"
#include "glview/logger.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qRegisterMetaType<ShaderUniform>("ShaderUniform");
    qRegisterMetaType<QList<ShaderUniform*>>("QList<ShaderUniform*>");

    qmlRegisterType<GLViewport>("GLRendering", 1, 0, "GLViewport");
    qmlRegisterType<ShaderUniform>("GLRendering", 1, 0, "ShaderUniform");

    QSurfaceFormat format;
    format.setVersion(3, 2);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setStencilBufferSize(8);


    QQmlApplicationEngine engine;

    //Logger& logger = Logger::instance();
    engine.rootContext()->setContextProperty("Logger", &Logger::instance());

    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QQuickWindow* window = qobject_cast<QQuickWindow*>(engine.rootObjects().first());
    window->setFormat(format);

    window->show();

    return app.exec();
}
