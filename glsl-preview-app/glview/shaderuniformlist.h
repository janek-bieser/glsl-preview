#ifndef SHADERUNIFORMLIST_H
#define SHADERUNIFORMLIST_H

#include <QAbstractListModel>
#include <QHash>

#include "shaderuniform.h"

class ShaderUniformList : public QAbstractListModel
{
    Q_OBJECT
public:
    enum UniformRole {
        TypeRole = Qt::UserRole + 1,
        NameRole
    };

    ShaderUniformList(QObject *parent = 0);
    ~ShaderUniformList();

    QHash<int, QByteArray> roleNames() const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    void add(const ShaderUniform& uniform);

public slots:
    void add(const QVariantMap& uMap);
    ShaderUniform* get(int idx) const;

private:
    QList<ShaderUniform*> m_uniforms;
};

#endif // SHADERUNIFORMLIST_H
