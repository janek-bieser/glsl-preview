#ifndef GLVIEWPORT_H
#define GLVIEWPORT_H

#include <QObject>
#include <QQuickFramebufferObject>

#include "glviewmessagebus.h"

class GLViewport : public QQuickFramebufferObject
{
public:
    GLViewport(QQuickItem* parent = NULL);
    ~GLViewport();

    QQuickFramebufferObject::Renderer* createRenderer() const override;

private:
    GLViewMessageBus* m_msgBus;
};

#endif // GLVIEWPORT_H
