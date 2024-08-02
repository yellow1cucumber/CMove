#pragma once

#include <QObject>
#include "qdir.h"
#include "qfile.h"
#include "qdiriterator.h"

#include "AnalisysResult.h"

class PathAnalisys : public QObject
{
	Q_OBJECT

public:
	PathAnalisys(QObject *parent);
	~PathAnalisys();

	AnalisysResult& Analize(const QString& sourcePath, const QString& substring);

	void FindAllSubDirectories(const QString& path, AnalisysResult& res);
	void FindAllFiles(const QString& path, AnalisysResult& res);
	void FindAllFilesByRegex(const QString& path, 
							 const QString& substring, 
							 AnalisysResult& res);
	AnalisysResult Result{ this };
};
