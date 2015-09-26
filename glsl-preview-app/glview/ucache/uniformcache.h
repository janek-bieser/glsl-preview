#ifndef UNIFORMCACHE
#define UNIFORMCACHE

#include <qopengl.h>

/*!
 * \brief Abstract base class for a uniform variable cache.
 */
class UniformCache
{
public:
    virtual ~UniformCache() = default;

    /*!
     * \brief Set uniform value for the current program.
     */
    virtual void setUniform() = 0;

    /*!
     * \brief Return the uniform type.
     * \return The uniform type.
     */
    virtual QString typeString() = 0;

    /*!
     * \brief Sets the location of the uniform within the shader.
     * \param value Location of the uniform.
     */
    void setLocation(GLint value) { m_location = value; }

    /*!
     * \brief Gets the location of the uniform within the shader.
     * \return Location of this uniform.
     */
    GLint location() const { return m_location; }

protected:
    GLint m_location;
};

#endif // UNIFORMCACHE

