#include "sampler2duniformcache.h"
#include <qdebug.h>
#include <qimage.h>
#include <qfile.h>
#include <qbytearray.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

static unsigned int curTexSlot = 0;

Sampler2DUniformCache::Sampler2DUniformCache(GLint location, const QString& imgSrc)
    : m_imgSrc(imgSrc)
{
    m_location = location;
    m_imgData = NULL;
    m_slot = curTexSlot++;
    reloadTexture();
}

Sampler2DUniformCache::Sampler2DUniformCache(const Sampler2DUniformCache &other)
{
    m_imgSrc = other.m_imgSrc;
    m_location = other.m_location;
    m_imgData = nullptr;
    m_slot = curTexSlot++;
    reloadTexture();
}

Sampler2DUniformCache::~Sampler2DUniformCache()
{
    stbi_image_free(m_imgData);
    glDeleteTextures(1, &m_texId);
}

void Sampler2DUniformCache::setImage(const QString& imageSrc)
{
    if (m_imgSrc != imageSrc) {
        m_imgSrc = imageSrc;
        reloadTexture();
    }
}

void Sampler2DUniformCache::setUniform()
{
    if (m_texId > 0) {
        glUniform1i(m_location, m_slot);
        glActiveTexture(GL_TEXTURE0 + m_slot);
        glBindTexture(GL_TEXTURE_2D, m_texId);
    }
}

QString Sampler2DUniformCache::typeString()
{
    return "sampler2d";
}

void Sampler2DUniformCache::reloadTexture()
{
    if (m_imgData != NULL) {
        stbi_image_free(m_imgData);
    }
    if (m_texId > 0) {
        glDeleteTextures(1, &m_texId);
    }

    const char* image_source = m_imgSrc.toStdString().c_str();
    int width, height, numComponent;
    stbi_set_flip_vertically_on_load(true);
    m_imgData = stbi_load(image_source, &width, &height, &numComponent, 4);
    qDebug() << stbi_failure_reason();

    glActiveTexture(GL_TEXTURE0 + m_slot);
    glGenTextures(1, &m_texId);
    glBindTexture(GL_TEXTURE_2D, m_texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imgData);

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
}
