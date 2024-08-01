#pragma once

#include <QObject>
#include "qdir.h"
#include "qfile.h"
#include "qdiriterator.h"

#include "AnalisysResult.h"

class PathAnalisys  : public QObject
{
	Q_OBJECT

public:
	PathAnalisys(QObject *parent);
	~PathAnalisys();

	void FindAllSubDirectories(const QString& path);
	void FindAllFiles(const QString& path);
	void FindAllFilesByRegex(const QString& path, const QString& substring);

private:
	AnalisysResult result{ this };
};
