#include "glviewport.h"
#include "glviewrenderer.h"

GLViewport::GLViewport(QQuickItem* parent) : QQuickFramebufferObject(parent)
{
    m_msgBus = new GLViewMessageBus();
}

GLViewport::~GLViewport()
{
    delete m_msgBus;
    m_msgBus = NULL;
}

QQuickFramebufferObject::Renderer* GLViewport::createRenderer() const
{
    return new GLViewRenderer(m_msgBus);
}
