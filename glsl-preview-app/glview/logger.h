#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

/*!
 * \brief Logging utility.
 */
class Logger : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief Get logger singleton instance.
     * \return Logger instance.
     */
    static Logger& instance();

    /*!
     * \brief Utility to log an error message.
     * \param message The error message.
     */
    static void error(const QString& message);

    /*!
     * \brief Utility to log an info message.
     * \param message The info message.
     */
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
