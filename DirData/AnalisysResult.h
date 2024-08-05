#pragma once

#include <QObject>
#include "qfile.h"
#include <qfileinfo.h>


class AnalisysResult : public QObject
{
	Q_OBJECT

public:
	AnalisysResult(QObject *parent);
	~AnalisysResult();

	void Reset();

	void SetFoundFilesCount(quint64 count) noexcept;
	void SetFoundSubdirsCount(quint64 count) noexcept;
	void SetFilesByRegexCount(quint64 count) noexcept;

	quint64 GetFoundFilesCount() const noexcept;
	quint64 GetFoundSubdirsCount() const noexcept;
	quint64 GetFilesByRegexCount() const noexcept;

	QStringList TargetFiles;

private:
	quint64 foundFilesCount{ 0 };
	quint64 foundSubDirsCount{ 0 };
	quint64 filesByRegexCount{ 0 };
};
