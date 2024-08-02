#include "AnalisysResult.h"

AnalisysResult::AnalisysResult(QObject *parent)
	: QObject(parent)
{
}

AnalisysResult::~AnalisysResult()
{
}

void AnalisysResult::Reset()
{
	this->foundFilesCount = 0;
	this->foundSubDirsCount = 0;
	this->filesByRegexCount = 0;
}

void AnalisysResult::SetFoundFilesCount(quint64 count) noexcept
{
	this->foundFilesCount = count;
}

void AnalisysResult::SetFoundSubdirsCount(quint64 count) noexcept
{
	this->foundSubDirsCount = count;
}

void AnalisysResult::SetFilesByRegexCount(quint64 count) noexcept
{
	this->filesByRegexCount = count;
}

quint64 AnalisysResult::GetFoundFilesCount() const noexcept
{
	return this->foundFilesCount;
}

quint64 AnalisysResult::GetFoundSubdirsCount() const noexcept
{
	return this->foundSubDirsCount;
}

quint64 AnalisysResult::GetFilesByRegexCount() const noexcept
{
	return this->filesByRegexCount;
}

