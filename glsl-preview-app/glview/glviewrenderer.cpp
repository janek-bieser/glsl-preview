#include "glviewrenderer.h"

GLViewRenderer::GLViewRenderer(GLViewMessageBus* msgBus) : QQuickFramebufferObject::Renderer()
{
    m_program = NULL;
    m_initialized = false;
    m_msgBus = msgBus;
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

    glClearColor(0.32, 0.65, 0.82, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLViewRenderer::setupGL()
{
    m_initialized = true;

    GLint glVersionMajor;
    GLint glVersionMinor;
    glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
    glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);
    QString glVersionString = QString::number(glVersionMajor) + "." + QString::number(glVersionMinor);

    m_msgBus->setGlVersion(glVersionString);

    QString vertex_source = "/Users/janekbieser/Desktop/shader_test/shader.vs";
    QString fragment_source = "/Users/janekbieser/Desktop/shader_test/shader.fs";

    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    vertexShader.compileSourceFile(vertex_source);
    QString vLog = vertexShader.log();
    if (vLog.size() > 0) {
        qDebug() << vLog;
    }

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    fragmentShader.compileSourceFile(fragment_source);
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
















