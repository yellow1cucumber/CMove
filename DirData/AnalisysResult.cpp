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

const QString AnalisysResult::ToString() const
{
	auto toUtf16 = QStringDecoder(QStringDecoder::System);

	QStringList rows{
		toUtf16("\t��������������� ������\t"),
		"\t" + QDateTime::currentDateTimeUtc().toString() + "\t",
		toUtf16("����� ���������� ������: ") + QString::number(this->foundFilesCount),
		toUtf16("���������� ��������� �����: ") + QString::number(this->foundSubDirsCount),
		toUtf16("���������� ������ �� �������: ") + QString::number(this->filesByRegexCount),
		toUtf16("����� ���������� ��������� �����: ")
	};
	auto targetFilesList{ "\t" + this->TargetFiles.join("\n\t")};
	rows.append(targetFilesList);
	auto res{ rows.join("\n") };

	return res;
}

