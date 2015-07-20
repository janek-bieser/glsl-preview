#include "shaderuniformlist.h"

#include <qdebug.h>

ShaderUniformList::ShaderUniformList(QObject *parent) : QAbstractListModel(parent)
{

}

ShaderUniformList::~ShaderUniformList()
{
    while (!m_uniforms.empty()) {
        ShaderUniform* u = m_uniforms.back();
        delete u;
        m_uniforms.pop_back();
    }
}

QHash<int, QByteArray> ShaderUniformList::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[TypeRole] = "type";
    roles[NameRole] = "name";
    return roles;
}

int ShaderUniformList::rowCount(const QModelIndex &/*parent*/) const
{
    return m_uniforms.count();
}

QVariant ShaderUniformList::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == TypeRole) {
        return m_uniforms[index.row()]->type();
    } else if (role == NameRole) {
        return m_uniforms[index.row()]->name();
    }

    return QVariant();
}

void ShaderUniformList::add(const ShaderUniform& uniform)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_uniforms.push_back(new ShaderUniform(uniform));
    endInsertRows();
}

// -----------------------------------------------------------------------------
// Slots
// -----------------------------------------------------------------------------

void ShaderUniformList::add(const QVariantMap& uMap)
{
    QString name = uMap.value("name").toString();
    QString type = uMap.value("type").toString();

    m_uniforms.push_back(new ShaderUniform(name, type));
}

ShaderUniform* ShaderUniformList::get(int idx) const
{
    if (idx < 0 || idx >= m_uniforms.count()) {
        return NULL;
    }

    return m_uniforms[idx];
}













