#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include <QQuickFramebufferObject>

#include "shaderuniformlist.h"

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

    QString glVersion();

    QColor backgroundColor();
    void setBackgroundColor(QColor color);

    ShaderUniformList* uniformModel();

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void wheelEvent(QWheelEvent* event) override;

public slots:
    void changeGLVersion(const QString& version);
    void updateUniform(const QVariantMap& uniform);
    void addUniform(const ShaderUniform& uniform);
    void reloadProgram();

signals:
    void glVersionChanged() const;
    void uniformChanged(const QVariantMap& uniform) const;
    void backgroundColorChanged(QColor color) const;
    void uniformModelChanged() const;
    void programChanged() const;

    void mouseMoved(const QPointF& point) const;
    void mouseWheel(qreal delta) const;


private:
    QString m_glVersion;
    QColor m_backgroundColor;
    QPointF m_lastMousePos;

    ShaderUniformList m_uniformList;
};

#endif // GLVIEWPORT_H
