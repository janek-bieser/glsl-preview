#ifndef GLVIEWMESSAGEBUS_H
#define GLVIEWMESSAGEBUS_H

#include <QObject>

class GLViewMessageBus : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString glVersion READ glVersion WRITE setGlVersion NOTIFY glVersionChanged)
public:
    explicit GLViewMessageBus(QObject *parent = 0);

    QString glVersion() const;
    void setGlVersion(const QString version);

signals:
    void glVersionChanged(const QString& version);

public slots:

private:
    QString m_glVersion;
};

#endif // GLVIEWMESSAGEBUS_H
