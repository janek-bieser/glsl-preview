#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include <QQuickFramebufferObject>

#include "shaderuniformlist.h"

/*!
 * \brief GLViewport is a QML compatible class which is used to communicate between the QML UI and the renderer.
 */
class GLViewport : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(QString glVersion READ glVersion NOTIFY glVersionChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
    Q_PROPERTY(ShaderUniformList* uniformModel READ uniformModel NOTIFY uniformModelChanged)
public:
    GLViewport(QQuickItem* parent = NULL);
    ~GLViewport();

    QQuickFramebufferObject::Renderer* createRenderer() const override;

    /*!
     * \brief Returns the OpenGL version of the driver.
     * \return The OpenGL version.
     */
    QString glVersion();

    /*!
     * \brief Returns the viewport background color.
     * \return The background color.
     */
    QColor backgroundColor();

    /*!
     * \brief Sets the viewport background color.
     * \param color The new color of the viewport.
     */
    void setBackgroundColor(QColor color);

    /*!
     * \brief Returns the list of all supported uniforms found in the GLSL program.
     * \return The list of uniforms.
     */
    ShaderUniformList* uniformModel();

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

public slots:
    /*!
     * \brief Slot to set the OpenGL version (used by the renderer).
     * \param version OpenGL version
     */
    void changeGLVersion(const QString& version);

    /*!
     * \brief Slot to update a uniform varaible (used by the UI).
     * \param uniform Data of the uniform variable.
     */
    void updateUniform(const QVariantMap& uniform);

    /*!
     * \brief Set the list of all uniforms at once.
     * \param uniforms The list of all uniforms.
     */
    void setUniforms(const QList<ShaderUniform*>& uniforms);

    /*!
     * \brief Load a new shader program.
     * \param vertex Path to vertex shader source code.
     * \param fragment Path to fragment shader source code.
     */
    void loadShaders(const QString& vertex, const QString& fragment);

    /*!
     * \brief Recompile the shader program.
     */
    void reloadProgram();

    /*!
     * \brief Select a 3D model to render in the viewport.
     * \param modelInfo Information about the model to render.
     */
    void selectModel(const QVariantMap& modelInfo);

    /*!
     * \brief Slot to let the viewport know about detected errors in the renderer.
     * \param errorMsg Error message.
     */
    void errorDetected(const QString& errorMsg);

    /*!
     * \brief Slot to let the viewport know about some kind of event.
     * \param type The message type (info, error)
     * \param message The message content.
     */
    void messageDetected(const QString& type, const QString& message);

signals:
    void glVersionChanged() const;
    void uniformChanged(const QVariantMap& uniform) const;
    void backgroundColorChanged(QColor color) const;
    void uniformModelChanged() const;
    void programChanged() const;
    void shaderSourceChanged(const QString& vertex, const QString& fragment) const;
    void modelSelected(const QVariantMap& modelInfo) const;
    void error(const QString& errorMsg) const;
    void message(const QString& type, const QString& messageText) const;

    void mouseMoved(const QPointF& point) const;
    void mouseWheel(qreal delta) const;


private:
    QString m_glVersion;
    QColor m_backgroundColor;
    QPointF m_lastMousePos;

    ShaderUniformList* m_uniformList;
};

#endif // GLVIEWPORT_H
