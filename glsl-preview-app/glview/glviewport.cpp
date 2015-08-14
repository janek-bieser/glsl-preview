#include "glviewport.h"
#include "glviewrenderer.h"

#include <QThread>

GLViewport::GLViewport(QQuickItem* parent) : QQuickFramebufferObject(parent)
{
    setAcceptedMouseButtons(Qt::AllButtons);
    m_uniformList = new ShaderUniformList();
}

GLViewport::~GLViewport()
{
    delete m_uniformList;
    m_uniformList = nullptr;
}

QQuickFramebufferObject::Renderer* GLViewport::createRenderer() const
{
    GLViewRenderer *renderer = new GLViewRenderer();

    connect(renderer, &GLViewRenderer::glVersionChanged, this, &GLViewport::changeGLVersion);
    connect(this, &GLViewport::uniformChanged, renderer, &GLViewRenderer::updateUniform);
    connect(this, &GLViewport::backgroundColorChanged, renderer, &GLViewRenderer::setBackgroundColor);
    connect(this, &GLViewport::programChanged, renderer, &GLViewRenderer::reloadProgram);

    connect(this, &GLViewport::mouseMoved, renderer, &GLViewRenderer::rotate);
    connect(this, &GLViewport::mouseWheel, renderer, &GLViewRenderer::camMove);

    connect(renderer, &GLViewRenderer::uniformsFound, this, &GLViewport::setUniforms);

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

ShaderUniformList* GLViewport::uniformModel()
{
    return m_uniformList;
}

void GLViewport::mousePressEvent(QMouseEvent* event)
{
    m_lastMousePos = event->localPos();
}

void GLViewport::mouseMoveEvent(QMouseEvent* event)
{
    if ( (event->buttons() & Qt::LeftButton) > 0) {
        QPointF currentPos = event->localPos();
        QPointF offset = currentPos - m_lastMousePos;
        m_lastMousePos = currentPos;

        emit mouseMoved(offset);
        update();
    }
}

void GLViewport::wheelEvent(QWheelEvent* event)
{
    GLfloat delta = (GLfloat) event->pixelDelta().y();
    emit mouseWheel(delta * 0.001);
    update();
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

void GLViewport::setUniforms(const QList<ShaderUniform*>& uniforms)
{
    ShaderUniformList* uList = new ShaderUniformList();
    uList->setUniforms(uniforms);
    delete m_uniformList;
    m_uniformList = uList;
    emit uniformModelChanged();

    for (auto it = uniforms.begin(); it != uniforms.end(); it++) {
        delete (*it);
    }
}

void GLViewport::reloadProgram()
{
    emit programChanged();
    update();
}





















