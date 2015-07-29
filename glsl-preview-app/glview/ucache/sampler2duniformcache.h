#ifndef SAMPLER2DUNIFORMCACHE_H
#define SAMPLER2DUNIFORMCACHE_H

#include "uniformcache.h"
#include <qstring.h>
#include <qopengltexture.h>

class Sampler2DUniformCache : public UniformCache
{
public:
    Sampler2DUniformCache(GLint location, const QString& imgSrc = "");
    ~Sampler2DUniformCache();

    void setImage(const QString& imageSrc);

    // UniformCache implementation
    void setUniform();

private:
    GLint m_location;
    QString m_imgSrc;
    QOpenGLTexture* m_texture;
    unsigned char* m_imgData;
    GLuint m_texId;

private:
    void reloadTexture();
};


#endif // SAMPLER2DUNIFORMCACHE_H
