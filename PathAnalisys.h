#pragma once

#include <QObject>
#include "qdir.h"
#include "qfile.h"
#include "qdiriterator.h"

class PathAnalisys  : public QObject
{
	Q_OBJECT

public:
	PathAnalisys(QObject *parent);
	~PathAnalisys();

	quint64 FindAllSubDirectories(const QString& path) const;
	quint64 FindAllFiles(const QString& path) const;
	quint64 FindAllFilesByRegex(const QString& path, const QString& substring) const;
};
