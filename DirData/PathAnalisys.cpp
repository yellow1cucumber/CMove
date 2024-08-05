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
	QDirIterator iter{ path, QDir::NoDotAndDotDot | QDir::Dirs, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	QStringList subdirs;
	while (iter.hasNext()) {
		QString path{ iter.next() };
		++count;
		subdirs.append(path);
	};
	res.SetFoundSubdirsCount(count);
}

void PathAnalisys::FindAllFiles(const QString& path, AnalisysResult& res)
{
	QDir dir{ path + "/" };
	QDirIterator iter{ dir.path(), QDir::Files, QDirIterator::Subdirectories };
	quint64 count{ 0 };
	while (iter.hasNext())
	{
		if (iter.next() != "." || iter.next() != ".") {
			++count;
		}
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
			QFileInfo fileInfo{ file };
			res.TargetFiles.append(fileInfo.fileName());
			++count;
		}
	}
	res.SetFilesByRegexCount(count);
}
