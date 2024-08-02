#include "AppSettings.h"

AppSettings::AppSettings(QObject* parent)
	: QObject(parent),
		params{ ".ini", QSettings::IniFormat }
{
}

AppSettings::~AppSettings()
{
}
