#ifndef UNIFORMCACHE_H
#define UNIFORMCACHE_H

#include "uniformcache.h"

class VecUniformCache : public UniformCache
{
public:
    VecUniformCache(GLint location, GLuint componentCount);
    VecUniformCache(const VecUniformCache& other);
    ~VecUniformCache();

    // UniformCache implementation
    void setUniform();
    QString typeString();

    GLuint componentCount() const;

    const GLfloat* values() const;
    void setValues(const GLfloat* values);

private:
    GLfloat* m_values;
    GLuint m_numComponent;
};

#endif // UNIFORMCACHE_H
