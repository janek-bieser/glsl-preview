#ifndef UNIFORMCACHE_H
#define UNIFORMCACHE_H

#include "uniformcache.h"

/*!
 * \brief A cache for a uniform of type <code>vec</code> or <code>float</code>.
 *        Floats are treated as vectors with one component.
 */
class VecUniformCache : public UniformCache
{
public:
    /*!
     * \brief Create a uniform cache for a <code>vec</code> variable.
     * \param location Uniform location
     * \param componentCount Number of components (1-4 are supported)
     */
    VecUniformCache(GLint location, GLuint componentCount);

    /*!
     * \brief VecUniformCache
     * \param other
     */
    VecUniformCache(const VecUniformCache& other);
    ~VecUniformCache();

    // UniformCache implementation
    void setUniform() override;
    QString typeString() override;

    /*!
     * \brief Returns the number of components.
     * \return Number of components.
     */
    GLuint componentCount() const;

    /*!
     * \brief Returns an array containing all the component values.
     * \return Values of all components.
     */
    const GLfloat* values() const;

    /*!
     * \brief Sets the values for all components.
     * \param values Values for all components.
     */
    void setValues(const GLfloat* values);

private:
    GLfloat* m_values;
    GLuint m_numComponent;
};

#endif // UNIFORMCACHE_H
