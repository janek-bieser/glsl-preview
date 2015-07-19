#include "shaderuniform.h"

ShaderUniform::ShaderUniform(QObject *parent) : QObject(parent)
{
}

ShaderUniform::ShaderUniform(const QString& name, const QString& type, QObject* parent)
    : QObject(parent), m_name(name), m_type(type)
{
}

ShaderUniform::ShaderUniform(const ShaderUniform& other, QObject* parent)
    : QObject(parent), m_name(other.name()), m_type(other.type())
{
}

ShaderUniform::~ShaderUniform()
{
}

QString ShaderUniform::name() const
{
    return m_name;
}

void ShaderUniform::setName(const QString& name)
{
    if (name != m_name) {
        m_name = name;
        emit nameChanged(m_name);
    }
}

QString ShaderUniform::type() const
{
    return m_type;
}

void ShaderUniform::setType(const QString& type)
{
    if (m_type != type) {
        m_type = type;
        emit typeChanged(m_type);
    }
}
