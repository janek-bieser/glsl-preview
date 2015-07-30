#ifndef GLVIEWRENDERER_H
#define GLVIEWRENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

#include "shaderuniform.h"
#include "renderables/renderable.h"
#include "ucache/uniformcache.h"

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

    void rotate(QPointF rotation);
    void camMove(GLfloat zMovement);

signals:
    void glVersionChanged(const QString& version);
    void backgroundColorChanged(QColor color);

    void uniformFound(const ShaderUniform& uniform);

private:
    QOpenGLShaderProgram* m_program;
    bool m_initialized;
    QString m_glVersion;
    QColor m_backgroundColor;
    Renderable* m_currentRenderable;
    Renderable* m_backgroundRenderable;
    QPointF m_objectRotation;
    GLfloat m_camZPos;

    QMap<QString, UniformCache*> m_uniformCache;

private:
    void setupGL();
    void parseUniforms();
};

#endif // GLVIEWRENDERER_H
