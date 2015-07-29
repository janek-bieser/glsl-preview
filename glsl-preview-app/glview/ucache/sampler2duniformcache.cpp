#include "sampler2duniformcache.h"
#include <qdebug.h>
#include <qimage.h>
#include <qfile.h>
#include <qbytearray.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Sampler2DUniformCache::Sampler2DUniformCache(GLint location, const QString& imgSrc)
    : m_location(location), m_imgSrc(imgSrc)
{
    m_imgData = NULL;
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

#define TEX_SLOT 0

void Sampler2DUniformCache::setUniform()
{
    if (m_texId > 0) {
        unsigned int texUnit = TEX_SLOT;
        glUniform1i(m_location, texUnit);
        glActiveTexture(GL_TEXTURE0 + texUnit);
        glBindTexture(GL_TEXTURE_2D, m_texId);
    }
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

    glActiveTexture(GL_TEXTURE0 + TEX_SLOT);
    glGenTextures(1, &m_texId);
    qDebug() << "current texture" << m_texId;
    glBindTexture(GL_TEXTURE_2D, m_texId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_imgData);

    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(GL_TEXTURE0);
}
