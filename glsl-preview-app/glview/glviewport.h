#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include <QQuickFramebufferObject>

class GLViewport : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(QString glVersion READ glVersion NOTIFY glVersionChanged)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged)
public:
    GLViewport(QQuickItem* parent = NULL);
    ~GLViewport();

    QQuickFramebufferObject::Renderer* createRenderer() const override;

    QString glVersion();

    QColor backgroundColor();
    void setBackgroundColor(QColor color);

    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

public slots:
    void changeGLVersion(const QString& version);
    void updateUniform(const QVariantMap& uniform);

signals:
    void glVersionChanged() const;
    void uniformChanged(const QVariantMap& uniform) const;
    void backgroundColorChanged(QColor color) const;

private:
    QString m_glVersion;
    QColor m_backgroundColor;
};

#endif // GLVIEWPORT_H
