#include "glviewrenderer.h"

#include <QColor>
#include <QThread>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

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

        GLuint progId = m_program->programId();

        glm::mat4 modelMat = glm::translate(glm::vec3(0, 0, 0));

        float rx = m_objectRotation.x();
        float ry = m_objectRotation.y();

        modelMat = glm::rotate(modelMat, rx * 2, glm::vec3(0, 1, 0));
        modelMat = glm::rotate(modelMat, -ry * 2, glm::vec3(1, 0, 0));

        glm::vec3 pos(0, 0, 1);
        glm::vec3 forward(0, 0, -1);
        glm::vec3 up(0, 1, 0);
        glm::mat4 viewMat = glm::lookAt(pos, pos + forward, up);

        QSize fbSize = this->framebufferObject()->size();
        glm::mat4 projMat = glm::perspective(45.0f, (GLfloat) fbSize.width() / fbSize.height(), 0.1f, -1000.0f);

        glm::mat4 MVP = projMat * viewMat * modelMat;

        GLint modelMatLoc = glGetUniformLocation(progId, "slp_ModelMatrix");
        if (modelMatLoc >= 0) {
            glUniformMatrix4fv(modelMatLoc, 1, GL_FALSE, &modelMat[0][0]);
        }

        GLint viewMatLoc = glGetUniformLocation(progId, "slp_ViewMatrix");
        if (viewMatLoc >= 0) {
            glUniformMatrix4fv(viewMatLoc, 1, GL_FALSE, &viewMat[0][0]);
        }

        GLint projMatLoc = glGetUniformLocation(progId, "slp_ProjectionMatrix");
        if (projMatLoc >= 0) {
            glUniformMatrix4fv(projMatLoc, 1, GL_FALSE, &projMat[0][0]);
        }

        GLint mvpMatrixLoc = glGetUniformLocation(progId, "slp_MVPMatrix");
        if (mvpMatrixLoc >= 0) {
            glUniformMatrix4fv(mvpMatrixLoc, 1, GL_FALSE, &MVP[0][0]);
        }

        for (auto it = m_uniformCache.begin(); it != m_uniformCache.end(); it++) {
            UniformCache* uc = it.value();
            uc->setUniform();
        }

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
    QString name = uniform.value("name").toString();
    QString type = uniform.value("type").toString();
    QList<QVariant> values = uniform.value("values").toList();
    int valuesLen = values.length();

    if (!m_uniformCache.contains(name)) {
        GLuint progId = m_program->programId();
        GLint loc = glGetUniformLocation(progId, name.toStdString().c_str());
        if (loc >= 0) {
            VecUniformCache* tmp = new VecUniformCache(loc, valuesLen);
            m_uniformCache[name] = tmp;
        } else {
            qWarning() << "trying to update non existing uniform";
        }
    }

    if (type.contains("vec")) {
        GLfloat floatValues[valuesLen];
        for (int i = 0; i < valuesLen; i++) {
            floatValues[i] = values[i].toFloat();
        }
        VecUniformCache* uc = (VecUniformCache*) m_uniformCache[name];
        uc->setValues(floatValues);
        update();
    }
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

void GLViewRenderer::rotate(QPointF rotation)
{
    m_objectRotation += (rotation * 0.002);
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

    parseUniforms();

    m_currentRenderable = new Quad(.5, .5);
}

typedef QHash<GLenum, QString> ShaderTypesHash;

ShaderTypesHash InitShaderTypes()
{
    ShaderTypesHash hash;

    hash[GL_FLOAT] = "float";

    hash[GL_FLOAT_VEC2] = "vec2";
    hash[GL_FLOAT_VEC3] = "vec3";
    hash[GL_FLOAT_VEC4] = "vec4";

    hash[GL_FLOAT_MAT2] = "mat2";
    hash[GL_FLOAT_MAT3] = "mat3";
    hash[GL_FLOAT_MAT4] = "mat4";

    hash[GL_SAMPLER_2D] = "sampler2D";

    return hash;
}

const ShaderTypesHash ShaderTypes = InitShaderTypes();

QString stringType(GLenum type)
{
    if (ShaderTypes.contains(type)) {
        return ShaderTypes[type];
    }
    return "UNKNOWN_TYPE";
}

void GLViewRenderer::parseUniforms()
{
    GLuint progId = m_program->programId();
    GLint numActiveUniforms;
    glGetProgramiv(progId, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

    for (int i = 0; i < numActiveUniforms; i++) {
        GLint size;
        GLenum type;
        GLsizei len;
        GLchar name[30];
        glGetActiveUniform(progId, i, 30, &len, &size, &type, name);

        QString uniformName = QString::fromUtf8(name);
        QString uniformType = stringType(type);

        ShaderUniform uniform;
        uniform.setName(uniformName);
        uniform.setType(uniformType);

        emit uniformFound(uniform);
    }
}
















