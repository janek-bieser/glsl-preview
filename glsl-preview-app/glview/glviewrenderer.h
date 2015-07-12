#ifndef GLVIEWRENDERER_H
#define GLVIEWRENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

#include "renderables/renderable.h"

class GLViewRenderer : public QObject, public QQuickFramebufferObject::Renderer
{
    Q_OBJECT
    Q_PROPERTY(QString glVersion READ glVersion NOTIFY glVersionChanged)
public:
    GLViewRenderer();
    ~GLViewRenderer();

    QOpenGLFramebufferObject* createFramebufferObject(const QSize &size) override;
    void render() override;

    QString glVersion() const;

public slots:
    void setBackgroundColor(QColor color);
    void updateUniform(const QVariantMap& uniform);
    void loadShader(const QString& vertex, const QString& fragment);

signals:
    void glVersionChanged(const QString& version);
    void backgroundColorChanged(QColor color);

private:
    QOpenGLShaderProgram* m_program;
    bool m_initialized;
    QString m_glVersion;
    QColor m_backgroundColor;

    Renderable* m_currentRenderable;

private:
    void setupGL();
};

class GLViewRendererBus : public QObject
{
};

#endif // GLVIEWRENDERER_H
