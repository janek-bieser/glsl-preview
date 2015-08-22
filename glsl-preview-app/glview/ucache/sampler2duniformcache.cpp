#include "sampler2duniformcache.h"
#include <qdebug.h>

#include "../logger.h"
#include "../texturecache.h"

Sampler2DUniformCache::Sampler2DUniformCache(GLint location, const QString& imgSrc)
    : m_imgSrc(imgSrc)
{
    m_location = location;
}

Sampler2DUniformCache::Sampler2DUniformCache(const Sampler2DUniformCache &other)
{
    m_imgSrc = other.m_imgSrc;
    m_location = other.m_location;
    TextureCache::LoadTexture(m_imgSrc);
}

Sampler2DUniformCache::~Sampler2DUniformCache()
{
}

void Sampler2DUniformCache::setImage(const QString& imageSrc)
{
    if (m_imgSrc != imageSrc) {
        m_imgSrc = imageSrc;
        TextureCache::LoadTexture(m_imgSrc);
    } else {
        TextureCache::Reloadtexture(m_imgSrc);
    }
}

void Sampler2DUniformCache::setUniform()
{
    TextureCache::BindTexture(m_imgSrc, m_location);
}

QString Sampler2DUniformCache::typeString()
{
    return "sampler2d";
}
