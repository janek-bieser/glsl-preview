#ifndef GLVIEWRENDERER_H
#define GLVIEWRENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

#include "shaderuniform.h"
#include "renderables/renderable.h"
#include "ucache/uniformcache.h"

/*!
 * \brief Renderer for GLViewport.
 */
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
    /*!
     * \brief Sets the background color. This will be used inside the <code>glClear</code> call.
     * \param color The background color.
     */
    void setBackgroundColor(QColor color);

    /*!
     * \brief Update the value of a uniform variable
     * \param uniform Uniform information.
     */
    void updateUniform(const QVariantMap& uniform);

    /*!
     * \brief Load new shader source code.
     * \param vertex Path to vertex shader source.
     * \param fragment Path to fragment shader source.
     */
    void loadShader(const QString& vertex, const QString& fragment);

    /*!
     * \brief Recompile the current shader program.
     */
    void reloadProgram();

    /*!
     * \brief Select a 3D model to render.
     * \param modelInfo Model information.
     */
    void selectModel(const QVariantMap& modelInfo);

    /*!
     * \brief Rotate the model.
     * \param rotation X and Y rotation
     */
    void rotate(QPointF rotation);

    /*!
     * \brief Move the camera in and out.
     * \param zMovement The amount of movement on the z-axis.
     */
    void camMove(GLfloat zMovement);

signals:
    /*!
     * \brief Emits this signel when the OpenGL Version is detected.
     * \param version OpenGL version.
     */
    void glVersionChanged(const QString& version);
    void backgroundColorChanged(QColor color);
    void error(const QString& error);
    void message(const QString& type, const QString& message);

    /*!
     * \brief Emits this signal afer the shader source is analysed and uniform variables are found.
     * \param uniforms list of the uniforms
     */
    void uniformsFound(const QList<ShaderUniform*>& uniforms);

    /*!
     * \brief Emitted when uniform parsing is complete.
     */
    void uniformParsingCompleted();

private:
    QOpenGLShaderProgram* m_program;
    QOpenGLShaderProgram* m_currentProgram;
    bool m_initialized;
    QString m_glVersion;
    QColor m_backgroundColor;

    Renderable* m_currentRenderable;
    Renderable* m_backgroundRenderable;
    QMap<QString, Renderable*> m_builtinRenderables;
    QMap<QString, Renderable*> m_customRenderables;

    QPointF m_objectRotation;
    GLfloat m_camZPos;
    QString m_vertexSource;
    QString m_fragmentSource;

    QMap<QString, UniformCache*> m_uniformCache;

private:
    void setupGL();
    void parseUniforms();
    void compileProgram();
    void updateUniformCache(const QList<ShaderUniform*>& uniforms);
};

#endif // GLVIEWRENDERER_H
