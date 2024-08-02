#pragma once

#include <QObject>
#include "qsettings.h"

class AppSettings : public QObject
{
	Q_OBJECT

public:
	AppSettings(QObject *parent);
	~AppSettings();

	QSettings params;
};
