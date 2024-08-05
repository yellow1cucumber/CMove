#pragma once

#include <QObject>

class Logger : public QObject
{
	Q_OBJECT

signals:
	void onNewMessage(const QString& message);

public slots:
	void WriteLog(const QString& message);

public:
	Logger(QObject *parent);
	~Logger();
};
