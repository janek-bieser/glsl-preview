#include "glviewport.h"
#include "glviewrenderer.h"

#include <QThread>

GLViewport::GLViewport(QQuickItem* parent) : QQuickFramebufferObject(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
}

GLViewport::~GLViewport()
{
}

QQuickFramebufferObject::Renderer* GLViewport::createRenderer() const
{
    GLViewRenderer *renderer = new GLViewRenderer();

    connect(renderer, &GLViewRenderer::glVersionChanged, this, &GLViewport::changeGLVersion);
    connect(this, &GLViewport::uniformChanged, renderer, &GLViewRenderer::updateUniform);
    connect(this, &GLViewport::backgroundColorChanged, renderer, &GLViewRenderer::setBackgroundColor);

    return renderer;
}

QString GLViewport::glVersion()
{
    return m_glVersion;
}

QColor GLViewport::backgroundColor()
{
    return m_backgroundColor;
}

void GLViewport::setBackgroundColor(QColor color)
{
    if (m_backgroundColor != color) {
        m_backgroundColor = color;
        emit backgroundColorChanged(m_backgroundColor);
        update();
    }
}

void GLViewport::mousePressEvent(QMouseEvent* event)
{
    qDebug() << event->localPos();
}

void GLViewport::mouseMoveEvent(QMouseEvent* event)
{
    if ( (event->buttons() & Qt::LeftButton) > 0) {
        qDebug() << event->localPos();
    }
}

// -----------------------------------------------------------------------------
// Slots
// -----------------------------------------------------------------------------

void GLViewport::changeGLVersion(const QString &version)
{
    if (m_glVersion != version) {
        m_glVersion = version;
        emit glVersionChanged();
    }
}

void GLViewport::updateUniform(const QVariantMap& uniform)
{
    emit uniformChanged(uniform);
}
