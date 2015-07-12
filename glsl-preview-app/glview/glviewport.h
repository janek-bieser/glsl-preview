#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include <QQuickFramebufferObject>

class GLViewport : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(QString glVersion READ glVersion NOTIFY glVersionChanged)
public:
    GLViewport(QQuickItem* parent = NULL);
    ~GLViewport();

    QQuickFramebufferObject::Renderer* createRenderer() const override;

    QString glVersion();

public slots:
    void changeGLVersion(const QString& version);
    void updateUniform(const QVariantMap& uniform);

signals:
    void glVersionChanged() const;
    void uniformChanged(const QVariantMap& uniform) const;

private:
    QString m_glVersion;
};

#endif // GLVIEWPORT_H
