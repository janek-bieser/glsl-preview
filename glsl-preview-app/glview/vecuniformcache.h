#ifndef UNIFORMCACHE_H
#define UNIFORMCACHE_H

#include "uniformcache.h"

class VecUniformCache : public UniformCache
{
public:
    VecUniformCache(GLint location, GLuint componentCount);
    ~VecUniformCache();

    void setUniform();

    GLint location() const;
    GLuint componentCount() const;

    const GLfloat* values() const;
    void setValues(const GLfloat* values);

private:
    GLfloat* m_values;
    GLuint m_numComponent;
    GLint m_location;
};

#endif // UNIFORMCACHE_H
