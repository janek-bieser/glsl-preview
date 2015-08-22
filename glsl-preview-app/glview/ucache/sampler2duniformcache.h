#ifndef SAMPLER2DUNIFORMCACHE_H
#define SAMPLER2DUNIFORMCACHE_H

#include "uniformcache.h"
#include <qstring.h>
#include <qopengltexture.h>

class Sampler2DUniformCache : public UniformCache
{
public:
    Sampler2DUniformCache(GLint location, const QString& imgSrc = "");
    Sampler2DUniformCache(const Sampler2DUniformCache& other);
    ~Sampler2DUniformCache();

    void setImage(const QString& imageSrc);

    // UniformCache implementation
    void setUniform();
    QString typeString();

private:
    QString m_imgSrc;
};


#endif // SAMPLER2DUNIFORMCACHE_H
