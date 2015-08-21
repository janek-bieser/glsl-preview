#include <qdebug.h>
#include "logger.h"

static Logger* loggerInstance = NULL;

Logger& Logger::instance()
{
    if (!loggerInstance) {
        loggerInstance = new Logger();
    }
    return *loggerInstance;
}

Logger::Logger(QObject *parent) : QObject(parent)
{

}

// -----------------------------------------------------------------------------
// Slots
// -----------------------------------------------------------------------------

void Logger::logError(const QString& message) const
{
    qDebug() << "Logger(error):" << message;
    emit errorMessage(message);
}

void Logger::logInfo(const QString &message) const
{
    qDebug() << "Logger(info):" << message;
    emit infoMessage(message);
}


// -----------------------------------------------------------------------------
// Static utility functions
// -----------------------------------------------------------------------------

void Logger::error(const QString &message)
{
    Logger::instance().logError(message);
}

void Logger::info(const QString &message)
{
    Logger::instance().logInfo(message);
}
