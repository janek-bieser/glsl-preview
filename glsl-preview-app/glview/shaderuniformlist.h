#ifndef SHADERUNIFORMLIST_H
#define SHADERUNIFORMLIST_H

#include <QAbstractListModel>
#include <QHash>

#include "shaderuniform.h"

/*!
 * \brief Represents the list of all found uniforms. The ShaderUniformList
 *        can be used as ListModel inside the QML User Interface.
 */
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

    /*!
     * \brief Adds a ShaderUniform to the list.
     * \param uniform A ShaderUniform object.
     */
    void add(const ShaderUniform& uniform);

    /*!
     * \brief Replace all uniform with a new list of uniforms..
     * \param uniforms List of new uniforms.
     */
    void setUniforms(const QList<ShaderUniform*>& uniforms);

    /*!
     * \brief Remove all unfiroms from the list.
     */
    void clear();

public slots:
    void add(const QVariantMap& uMap);

    /*!
     * \brief Gets a uniform at a specific index.
     * \param idx The index
     * \return  A ShaderUniform object.
     */
    ShaderUniform* get(int idx) const;

private:
    QList<ShaderUniform*> m_uniforms;

    bool contains(const ShaderUniform& su);
};

#endif // SHADERUNIFORMLIST_H
