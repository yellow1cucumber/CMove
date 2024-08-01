#include "PathAnalisys.h"

PathAnalisys::PathAnalisys(QObject *parent)
	: QObject(parent)
{}

PathAnalisys::~PathAnalisys()
{}

quint64 PathAnalisys::FindAllSubDirectories(const QString & path) const
{
	QDir dir{ path };
	QDirIterator iter{ dir, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext()) {
		count++;
	};
	return count;
}

quint64 PathAnalisys::FindAllFiles(const QString& path) const
{
	QDir dir{ path };
	QDirIterator iter{ dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext())
	{
		count++;
	}
	return count;
}

quint64 PathAnalisys::FindAllFilesByRegex(const QString& path, const QString& substring) const
{
	QDir dir{ path };
	QDirIterator iter{ dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext())
	{
		auto file = iter.next();
		if (file.contains(substring)) {
			count++;
		}
	}
	return quint64();
}
