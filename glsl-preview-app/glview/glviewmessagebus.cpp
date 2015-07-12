#include "glviewmessagebus.h"
#include <qdebug.h>

GLViewMessageBus::GLViewMessageBus(QObject *parent) : QObject(parent)
{

}

QString GLViewMessageBus::glVersion() const
{
    return m_glVersion;
}

void GLViewMessageBus::setGlVersion(const QString version)
{
    if (m_glVersion != version) {
        m_glVersion = version;
    }
}

