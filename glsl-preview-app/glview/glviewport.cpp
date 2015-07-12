#include "glviewport.h"
#include "glviewrenderer.h"

GLViewport::GLViewport(QQuickItem* parent) : QQuickFramebufferObject(parent)
{
}

GLViewport::~GLViewport()
{
}

QQuickFramebufferObject::Renderer* GLViewport::createRenderer() const
{
    GLViewRenderer *renderer = new GLViewRenderer();

    connect(renderer, &GLViewRenderer::glVersionChanged, this, &GLViewport::changeGLVersion);
    connect(this, &GLViewport::uniformChanged, renderer, &GLViewRenderer::updateUniform);

    return renderer;
}

QString GLViewport::glVersion()
{
    return m_glVersion;
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
