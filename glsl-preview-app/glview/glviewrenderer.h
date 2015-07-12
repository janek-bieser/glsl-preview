#ifndef GLVIEWRENDERER_H
#define GLVIEWRENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

#include "glviewmessagebus.h"

class GLViewRenderer : public QQuickFramebufferObject::Renderer
{
public:
    GLViewRenderer(GLViewMessageBus* msgBus);
    ~GLViewRenderer();

    QOpenGLFramebufferObject* createFramebufferObject(const QSize &size) override;
    void render() override;

private:
    QOpenGLShaderProgram* m_program;
    bool m_initialized;
    GLViewMessageBus* m_msgBus;

private:
    void setupGL();
};

class GLViewRendererBus : public QObject
{
};

#endif // GLVIEWRENDERER_H
