#include "glviewrenderer.h"

#include <vector>

#include <QColor>
#include <QThread>
#include <QRegularExpression>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>

#include "renderables/quad.h"
#include "renderables/cube.h"
#include "renderables/objmodel.h"
#include "ucache/vecuniformcache.h"
#include "ucache/sampler2duniformcache.h"
#include "shaders/shaderlibrary.h"
#include "logger.h"

GLViewRenderer::GLViewRenderer() : QQuickFramebufferObject::Renderer()
{
    m_program = NULL;
    m_initialized = false;
    m_currentRenderable = NULL;
    m_backgroundRenderable = NULL;
    m_camZPos = 1;

    //m_vertexSource = "/Users/janekbieser/Desktop/shader_test/src/pbr2.vs";
    //m_fragmentSource = "/Users/janekbieser/Desktop/shader_test/src/pbr2.fs";
    m_vertexSource = "";
    m_fragmentSource = "";
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

void setUniformMatrix4f(GLuint progId, const char* name, const glm::mat4& value)
{
    GLint matLoc = glGetUniformLocation(progId, name);
    if (matLoc >= 0) {
        glUniformMatrix4fv(matLoc, 1, GL_FALSE, &value[0][0]);
    }
}

void setUniformMatrix3f(GLuint progId, const char* name, const glm::mat3& value)
{
    GLint matLoc = glGetUniformLocation(progId, name);
    if (matLoc >= 0) {
        glUniformMatrix3fv(matLoc, 1, GL_FALSE, &value[0][0]);
    }
}

void setUniformVec4(GLuint progId, const char* name, const glm::vec4& value)
{
    GLint matLoc = glGetUniformLocation(progId, name);
    if (matLoc >= 0) {
        glUniform4fv(matLoc, 1, &value[0]);
    }
}

void setUniformVec2(GLuint progId, const char* name, const glm::vec2& value)
{
    GLint matLoc = glGetUniformLocation(progId, name);
    if (matLoc >= 0) {
        glUniform2fv(matLoc, 1, &value[0]);
    }
}

void GLViewRenderer::render()
{
    if (!m_initialized) {
        this->setupGL();
    }

    // TODO(janek) only enable for 3d models, not for basic plane
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    glClearColor(m_backgroundColor.redF(), m_backgroundColor.greenF(), m_backgroundColor.blueF(), 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QSize fbSize = this->framebufferObject()->size();

    if (m_backgroundRenderable) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glDisable(GL_DEPTH_TEST);
        QOpenGLShaderProgram* prog = ShaderLibrary::getShader(ShaderLibrary::CheckerShader);
        prog->bind();

        glm::vec2 size(fbSize.width(), fbSize.height());
        glm::vec2 normalizedSize = glm::normalize(size);
        float factor = normalizedSize.x > normalizedSize.y ? normalizedSize.x : normalizedSize.y;
        glm::vec2 scale = normalizedSize * (factor * 10.0f);
        setUniformVec2(prog->programId(), "Scale", scale);

        m_backgroundRenderable->render();
        glEnable(GL_DEPTH_TEST);
        glDisable(GL_BLEND);
    }

    if (m_currentRenderable) {
        //m_program->bind();
        m_currentProgram->bind();

        //GLuint progId = m_program->programId();
        GLuint progId = m_currentProgram->programId();

        glm::mat4 modelMat = glm::translate(glm::vec3(0, 0, 0));

        float rx = m_objectRotation.x();
        float ry = m_objectRotation.y();

        modelMat = glm::rotate(modelMat, rx * 2, glm::vec3(0, 1, 0));
        modelMat = glm::rotate(modelMat, -ry * 2, glm::vec3(1, 0, 0));

        glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(modelMat)));

        glm::vec3 pos(0, 0, m_camZPos);
        glm::vec3 forward(0, 0, -1);
        glm::vec3 up(0, 1, 0);
        glm::mat4 viewMat = glm::lookAt(pos, pos + forward, up);

        GLfloat fov = 75 * (M_PI / 180.0f);
        glm::mat4 projMat = glm::perspectiveFov(fov, (GLfloat) fbSize.width(), (GLfloat) fbSize.height(), 0.1f, -1000.0f);

        glm::mat4 MVP = projMat * viewMat * modelMat;

        setUniformMatrix3f(progId, "slp_NormalMatrix", normalMat);

        setUniformMatrix4f(progId, "slp_ModelMatrix", modelMat);
        setUniformMatrix4f(progId, "slp_ViewMatrix", viewMat);
        setUniformMatrix4f(progId, "slp_ProjectionMatrix", projMat);
        setUniformMatrix4f(progId, "slp_MVPMatrix", MVP);

        GLuint texId = QOpenGLTexture::boundTextureId(0, QOpenGLTexture::BindingTarget2D);

        for (auto it = m_uniformCache.begin(); it != m_uniformCache.end(); it++) {
            UniformCache* uc = it.value();
            uc->setUniform();
        }

        m_currentRenderable->render();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texId);
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
        GLuint progId = m_currentProgram->programId();
        GLint loc = glGetUniformLocation(progId, name.toStdString().c_str());

        if (loc >= 0) {

            if (type.contains("vec")) {
                VecUniformCache* tmp = new VecUniformCache(loc, valuesLen);
                m_uniformCache[name] = tmp;
            } else if (type == "sampler2D") {
                Sampler2DUniformCache* tmp = new Sampler2DUniformCache(loc);
                m_uniformCache[name] = tmp;
            }

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
    } else if (type == "sampler2D") {
        Sampler2DUniformCache* uc = (Sampler2DUniformCache*) m_uniformCache[name];
        uc->setImage(values[0].toString());
        update();
    }
}

void GLViewRenderer::loadShader(const QString& vertex, const QString& fragment)
{
    m_vertexSource = vertex;
    m_fragmentSource = fragment;
    compileProgram();
    parseUniforms();
    update();
}

void GLViewRenderer::rotate(QPointF rotation)
{
    m_objectRotation += (rotation * 0.002);
}

void GLViewRenderer::camMove(GLfloat zMovement)
{
    m_camZPos += (GLfloat)zMovement;
}

void GLViewRenderer::reloadProgram()
{
    loadShader(m_vertexSource, m_fragmentSource);
    parseUniforms();
}

void GLViewRenderer::selectModel(const QVariantMap &modelInfo)
{
    QString name = modelInfo.value("name").toString();
    if (modelInfo.contains("path")) {
        QString path = modelInfo.value("path").toString();
        if (m_customRenderables.contains(path)) {
            m_currentRenderable = m_customRenderables[path];
            update();
        } else {
            m_customRenderables[path] = new OBJModel(path);
            m_currentRenderable = m_customRenderables[path];
            update();
        }
    } else {
        if (m_builtinRenderables.contains(name)) {
            m_currentRenderable = m_builtinRenderables[name];
            update();
        }
    }
}

// -----------------------------------------------------------------------------
// Private
// -----------------------------------------------------------------------------

void GLViewRenderer::compileProgram()
{
    if (m_vertexSource == "" || m_fragmentSource == "") {
        Logger::info("Using default shader.");
        m_currentProgram = ShaderLibrary::getShader(ShaderLibrary::SolidFillShader);
        return;
    }

    qDebug() << "Loading Shader(" << m_vertexSource << "," << m_fragmentSource << ")";
    QOpenGLShader vertexShader(QOpenGLShader::Vertex);
    vertexShader.compileSourceFile(m_vertexSource);
    QString vLog = vertexShader.log();
    if (vLog.size() > 0) {
        Logger::error("Vertex Shader : " + vLog);
    }

    QOpenGLShader fragmentShader(QOpenGLShader::Fragment);
    fragmentShader.compileSourceFile(m_fragmentSource);
    QString fLog = fragmentShader.log();
    if (fLog.size() > 0) {
        Logger::error("Fragment Shader : " + fLog);
    }

    if (m_program != nullptr) {
        delete m_program;
    }

    m_program = new QOpenGLShaderProgram();
    m_program->addShader(&vertexShader);
    m_program->addShader(&fragmentShader);
    m_program->link();

    QString progLog = m_program->log();
    if (progLog.size() > 0) {
        Logger::error(progLog);
    }

    m_currentProgram = m_program;
}

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

    ShaderLibrary::compileAll();

    //compileProgram();
    m_program = nullptr;
    m_currentProgram = ShaderLibrary::getShader(ShaderLibrary::SolidFillShader);

    parseUniforms();

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    m_builtinRenderables["Plane"] = new Quad(.5, .5);
    m_builtinRenderables["Cube"] = new Cube(.5);

    m_currentRenderable = m_builtinRenderables["Plane"];
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
    GLuint progId = m_currentProgram->programId();
    GLint numActiveUniforms;
    glGetProgramiv(progId, GL_ACTIVE_UNIFORMS, &numActiveUniforms);

    QList<ShaderUniform*> foundUniforms;

    for (int i = 0; i < numActiveUniforms; i++) {
        GLint size;
        GLenum type;
        GLsizei len;
        GLchar name[30];
        glGetActiveUniform(progId, i, 30, &len, &size, &type, name);

        QString uniformName = QString::fromUtf8(name);
        QString uniformType = stringType(type);

        ShaderUniform* uniform = new ShaderUniform(uniformName, uniformType);
        foundUniforms.push_back(uniform);
    }

    updateUniformCache(foundUniforms);
    emit uniformsFound(foundUniforms);
}

void GLViewRenderer::updateUniformCache(const QList<ShaderUniform*>& uniforms)
{
    QMap<QString, UniformCache*> oldCache = m_uniformCache;
    QMap<QString, UniformCache*> newCache;

    int len = uniforms.size();
    GLuint progId = m_currentProgram->programId();

    for (int i = 0; i < len; i++) {
        ShaderUniform* s = uniforms[i];

        // if the same variable exists in the old cache (name and type have to match)
        if (oldCache.contains(s->name()) && s->type() == oldCache[s->name()]->typeString()) {

            GLint loc = glGetUniformLocation(progId, s->name().toStdString().c_str());

            if (loc >= 0) {

                if (s->type().contains("vec") || s->type() == "float") {
                    VecUniformCache* oldC = static_cast<VecUniformCache*>(oldCache[s->name()]);
                    UniformCache* c = new VecUniformCache(*oldC);
                    c->setLocation(loc);
                    newCache[s->name()] = c;
                } else if (s->type() == "sampler2d") {
                    Sampler2DUniformCache* oldC = static_cast<Sampler2DUniformCache*>(oldCache[s->name()]);
                    UniformCache* c = new Sampler2DUniformCache(*oldC);
                    c->setLocation(loc);
                    newCache[s->name()] = c;
                }

            }
        }

    }

    m_uniformCache = newCache;

    for (auto it = oldCache.begin(); it != oldCache.end(); it++) {
        delete *it;
    }
}
















