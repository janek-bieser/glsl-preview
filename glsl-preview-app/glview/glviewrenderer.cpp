#include "glviewrenderer.h"

#include <QColor>
#include <QThread>

#include "renderables/quad.h"

GLViewRenderer::GLViewRenderer() : QQuickFramebufferObject::Renderer()
{
    m_program = NULL;
    m_initialized = false;
    m_currentRenderable = NULL;
}

GLViewRenderer::~GLViewRenderer()
{
    if (m_program) {
        delete m_program;
        m_program = NULL;
    }
}

QOpenGLFramebufferObject* GLViewRenderer::createFramebufferObject(const QSize &size)
{
    QOpenGLFramebufferObjectFormat format;
    format.setAttachment(QOpenGLFramebufferObject::CombinedDepthStencil);
    return new QOpenGLFramebufferObject(size, format);
}

void GLViewRenderer::render()
{
    if (!m_initialized) {
        this->setupGL();
    }

    glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (m_currentRenderable) {
        m_program->bind();
        m_currentRenderable->render();
    }
}

QString GLViewRenderer::glVersion() const
{
    return m_glVersion;
}

void GLViewRenderer::setBackgroundColor(QColor color)
{
    if (m_backgroundColor != color) {
        m_backgroundColor = color;
        update();
    }
}

// -----------------------------------------------------------------------------
// Slots
// -----------------------------------------------------------------------------

void GLViewRenderer::updateUniform(const QVariantMap& uniform)
{
    qDebug() << "update uniform" << uniform.value("name");
}

void GLViewRenderer::loadShader(const QString& vertex, const QString& fragment)
{
    qDebug() << "Loading Shader(" << vertex << "," << fragment << ")";
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    vertexShader.compileSourceFile(vertex);
    QString vLog = vertexShader.log();
    if (vLog.size() > 0) {
        qDebug() << vLog;
    }

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    fragmentShader.compileSourceFile(fragment);
    QString fLog = fragmentShader.log();
    if (fLog.size() > 0) {
        qDebug() << fLog;
    }

    m_program = new QOpenGLShaderProgram();
    m_program->addShader(&vertexShader);
    m_program->addShader(&fragmentShader);
    m_program->link();

    QString progLog = m_program->log();
    if (progLog.size() > 0) {
        qDebug() << progLog;
    }
}

// -----------------------------------------------------------------------------
// Private
// -----------------------------------------------------------------------------

void GLViewRenderer::setupGL()
{
    m_initialized = true;

    GLint glVersionMajor;
    GLint glVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);
    QString glVersionString = QString::number(glVersionMajor) + "." + QString::number(glVersionMinor);

    m_glVersion = glVersionString;
    emit glVersionChanged(m_glVersion);

    QString vertex_source = "/Users/janekbieser/Desktop/shader_test/shader.vs";
    QString fragment_source = "/Users/janekbieser/Desktop/shader_test/shader.fs";

    loadShader(vertex_source, fragment_source);

    m_currentRenderable = new Quad(1, 1);
}
















