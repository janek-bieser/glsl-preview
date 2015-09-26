#ifndef SAMPLER2DUNIFORMCACHE_H
#define SAMPLER2DUNIFORMCACHE_H

#include "uniformcache.h"
#include <qstring.h>
#include <qopengltexture.h>

/*!
 * \brief A cache for a uniform of type <code>sampler2D</code>.
 */
class Sampler2DUniformCache : public UniformCache
{
public:
    /*!
     * \brief Create a uniform cache for a <code>sampler2D</code> variable.
     * \param location Uniform location
     * \param imgSrc Path to the image.
     */
    Sampler2DUniformCache(GLint location, const QString& imgSrc = "");

    Sampler2DUniformCache(const Sampler2DUniformCache& other);
    ~Sampler2DUniformCache();

    /*!
     * \brief Sets the image path.
     * \param imageSrc Path to the image.
     */
    void setImage(const QString& imageSrc);

    // UniformCache implementation
    void setUniform() override;
    QString typeString() override;

private:
    QString m_imgSrc;
};


#endif // SAMPLER2DUNIFORMCACHE_H
