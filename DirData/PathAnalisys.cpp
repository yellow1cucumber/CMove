#include "PathAnalisys.h"

PathAnalisys::PathAnalisys(QObject *parent)
	: QObject(parent)
{}

PathAnalisys::~PathAnalisys()
{}

AnalisysResult& PathAnalisys::Analize(const QString & sourcePath, const QString & substring)
{
	this->Result.Reset();
	this->FindAllSubDirectories(sourcePath, this->Result);
	this->FindAllFiles(sourcePath, this->Result);
	this->FindAllFilesByRegex(sourcePath, substring, this->Result);

	return this->Result;
}

void PathAnalisys::FindAllSubDirectories(const QString& path, AnalisysResult& res)
{
	QDir dir{ path };
	QDirIterator iter{ dir, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext()) {
		res.Subdirs.append(iter.next());
		++count;
	};
	res.SetFoundSubdirsCount(count - 2);
}

void PathAnalisys::FindAllFiles(const QString& path, AnalisysResult& res)
{
	QDir dir{ path + "/" };
	QDirIterator iter{ dir.path(), QDir::Files, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext())
	{
		QString iterPath = iter.path();
		QString filePath = iter.next();
		++count;
	}
	res.SetFoundFilesCount(count);
}

void PathAnalisys::FindAllFilesByRegex(const QString& path, const QString& substring, AnalisysResult& res)
{
	QDir dir{ path + "/" };
	QDirIterator iter{ dir.path(), QDir::Files, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext())
	{
		auto file = iter.next();
		if (file.contains(substring)) {
			res.FilesByRegex.append(file);
			++count;
		}
	}
	res.SetFilesByRegexCount(count);
}
