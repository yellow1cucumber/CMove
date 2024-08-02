#include "AppSettings.h"

AppSettings::AppSettings(QObject* parent)
	: QObject(parent),
		params{ QSettings::IniFormat, QSettings::UserScope, "", "" }
{
}

AppSettings::~AppSettings()
{
}
