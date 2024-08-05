#include "Logger.h"

Logger::Logger(QObject *parent)
	: QObject(parent)
{
}

Logger::~Logger()
{
}

void Logger::WriteLog(const QString& message) {
	emit onNewMessage(message);
}
