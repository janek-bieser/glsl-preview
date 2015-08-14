#ifndef UNIFORMCACHE
#define UNIFORMCACHE

#include <qopengl.h>

class UniformCache
{
public:
    virtual ~UniformCache() = default;
    virtual void setUniform() = 0;
    virtual QString typeString() = 0;

    void setLocation(GLint value) { m_location = value; }
    GLint location() const { return m_location; }

protected:
    GLint m_location;
};

#endif // UNIFORMCACHE

