#include "vecuniformcache.h"
#include <stdlib.h>
#include <qdebug.h>

VecUniformCache::VecUniformCache(GLint location, GLuint componentCount)
    : m_numComponent(componentCount), m_location(location)
{
    m_values = (GLfloat*) calloc(m_numComponent, sizeof(GLfloat));
}

VecUniformCache::~VecUniformCache()
{
    free(m_values);
    m_values = NULL;
}

void VecUniformCache::setUniform()
{
    switch (componentCount()) {
    case 1:
        glUniform1fv(location(), 1, values());
        break;
    case 2:
        glUniform2fv(location(), 1, values());
        break;
    case 3:
        glUniform3fv(location(), 1, values());
        break;
    case 4:
        glUniform4fv(location(), 1, values());
        break;
    default:
        qDebug() << "trying to set unknown vector uniform";
        break;
    }
}

GLint VecUniformCache::location() const
{
    return m_location;
}

GLuint VecUniformCache::componentCount() const
{
    return m_numComponent;
}

const GLfloat* VecUniformCache::values() const
{
    return m_values;
}

void VecUniformCache::setValues(const GLfloat *values)
{
    memcpy(m_values, values, sizeof(GLfloat) * componentCount());
}

