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
    if (!contains(uniform)) {
        beginInsertRows(QModelIndex(), rowCount(), rowCount());
        m_uniforms.push_back(new ShaderUniform(uniform));
        endInsertRows();
    }
}

void ShaderUniformList::setUniforms(const QList<ShaderUniform*>& uniforms)
{
    int len = uniforms.length();
    for (int i = 0; i < len; i++) {
        add(*uniforms[i]);
    }
}

void ShaderUniformList::clear()
{
    while(!m_uniforms.isEmpty()) {
        beginRemoveRows(QModelIndex(), rowCount(), rowCount());
        ShaderUniform* u = m_uniforms.last();
        delete u;
        m_uniforms.pop_back();
        endRemoveRows();
    }
}

// -----------------------------------------------------------------------------
// Slots
// -----------------------------------------------------------------------------

void ShaderUniformList::add(const QVariantMap& uMap)
{
    QString name = uMap.value("name").toString();
    QString type = uMap.value("type").toString();
    ShaderUniform* u = new ShaderUniform(name, type);

    if (!contains(*u)) {
        m_uniforms.push_back(u);
    }
}

ShaderUniform* ShaderUniformList::get(int idx) const
{
    if (idx < 0 || idx >= m_uniforms.count()) {
        return NULL;
    }

    return m_uniforms[idx];
}

// -----------------------------------------------------------------------------
// private
// -----------------------------------------------------------------------------

bool ShaderUniformList::contains(const ShaderUniform& su)
{
    int len = m_uniforms.length();
    bool found = false;

    for (int i = 0; i < len && !found; i++) {
        ShaderUniform* current = m_uniforms[i];
        if (su.name() == current->name()) {
            found = true;
        }
    }

    return found;
}










