#ifndef SHADERUNIFORM_H
#define SHADERUNIFORM_H

#include <QObject>

class ShaderUniform : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
public:
    explicit ShaderUniform(QObject *parent = 0);
    explicit ShaderUniform(const QString& name, const QString& type, QObject* parent = 0);
    explicit ShaderUniform(const ShaderUniform& other, QObject* parent = 0);
    ~ShaderUniform();

    QString name() const;
    void setName(const QString& name);

    QString type() const;
    void setType(const QString& type);

signals:
    void nameChanged(const QString& name);
    void typeChanged(const QString& type);

public slots:

private:
    QString m_name;
    QString m_type;

};

inline bool
operator ==(const ShaderUniform& lhs, const ShaderUniform& rhs)
{
    return lhs.name() == rhs.name() && lhs.type() == rhs.type();
}

#endif // SHADERUNIFORM_H
