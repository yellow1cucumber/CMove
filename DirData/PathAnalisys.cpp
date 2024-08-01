#include "PathAnalisys.h"

PathAnalisys::PathAnalisys(QObject *parent)
	: QObject(parent)
{}

PathAnalisys::~PathAnalisys()
{}

void PathAnalisys::FindAllSubDirectories(const QString & path)
{
	QDir dir{ path };
	QDirIterator iter{ dir, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext()) {
		this->result.Subdirs.append(iter.next());
		count++;
	};
	this->result.SetFoundSubdirsCount(count);
}

void PathAnalisys::FindAllFiles(const QString& path)
{
	QDir dir{ path };
	QDirIterator iter{ dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext())
	{
		count++;
	}
	this->result.SetFoundFilesCount(count);
}

void PathAnalisys::FindAllFilesByRegex(const QString& path, const QString& substring)
{
	QDir dir{ path };
	QDirIterator iter{ dir.absolutePath(), QDir::Files, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext())
	{
		auto file = iter.next();
		if (file.contains(substring)) {
			this->result.FilesByRegex.append(file);
			count++;
		}
	}
	this->result.SetFilesByRegexCount(count);
}
