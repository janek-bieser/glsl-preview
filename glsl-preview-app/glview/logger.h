#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class Logger : public QObject
{
    Q_OBJECT
public:
    static Logger& instance();

    static void error(const QString& message);
    static void info(const QString& message);

signals:
    void errorMessage(const QString& message) const;
    void infoMessage(const QString& message) const;

public slots:
    void logError(const QString& message) const;
    void logInfo(const QString& message) const;

private:
    explicit Logger(QObject *parent = 0);
};

#endif // LOGGER_H
