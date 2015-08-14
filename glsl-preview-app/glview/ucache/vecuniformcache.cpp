#include "vecuniformcache.h"
#include <stdlib.h>
#include <qdebug.h>

VecUniformCache::VecUniformCache(GLint location, GLuint componentCount)
    : m_numComponent(componentCount)
{
    m_values = (GLfloat*) calloc(m_numComponent, sizeof(GLfloat));
    m_location = location;
}

VecUniformCache::VecUniformCache(const VecUniformCache &other)
{
    m_numComponent = other.m_numComponent;
    m_location = other.m_location;
    m_values = (GLfloat*) calloc(m_numComponent, sizeof(GLfloat));
    for (int i = 0; i < m_numComponent; i++) {
        m_values[i] = other.m_values[i];
    }
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

QString VecUniformCache::typeString()
{
    QString type = "";
    switch (componentCount()) {
    case 1:
        type = "float";
        break;
    case 2:
    case 3:
    case 4:
        type = "vec" + componentCount();
        break;
    default:
        qDebug() << "unknown vector type";
        break;
    }

    return type;
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

