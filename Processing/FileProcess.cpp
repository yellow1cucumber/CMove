#include "FileProcess.h"

FileProcess::FileProcess(QObject *parent)
	: QObject(parent)
{
}

FileProcess::~FileProcess()
{
}

bool FileProcess::StartTransaction(TransactionParametres& params)
{
    bool success = false;
    QDir sourceDir{ params.SourceFolder };

    if (!sourceDir.exists()) {
        return false;
    }

    QDir destDir(params.DestinationFolder);
    if (!destDir.exists()) {
        destDir.mkdir(params.DestinationFolder);
    }


    QStringList files{ sourceDir.entryList(QDir::Files) };
    for (const QString& file : files) {
        QString srcName = params.SourceFolder + QDir::separator() + file;
        QString destName = params.DestinationFolder + QDir::separator() + file;

        switch (params.Type)
        {
        case TransactionParametres::TransactionType::Copy:
            success = this->Copy(srcName, destName, params.Rewrite);
            if (!success) {
                return false;
            }
            break;

        case TransactionParametres::TransactionType::Move:
            success = this->Move(srcName, destName, params.Rewrite);
            if (!success) {
                return false;
            }
            break;

        default:
            break;
        }
    }
    files.clear();


    files = sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot);
    for (const QString& file : files) {
        QString srcName = params.SourceFolder + QDir::separator() + file;
        QString destName = params.DestinationFolder + QDir::separator() + file;

        params.SourceFolder = srcName;
        params.DestinationFolder = destName;

        success = this->StartTransaction(params);
        if (!success) {
            return false;
        }
    }
    return true;
}

const bool FileProcess::IsFileExists(const QString& file) const noexcept
{
    return QFile::exists(file);
}

const bool FileProcess::Copy(const QString& source, const QString& dest, const bool rewrite)
{
    if (IsFileExists(dest) && rewrite == false) {
        return true;
    }
    return QFile::copy(source, dest);
}

const bool FileProcess::Move(const QString& source, const QString& dest, const bool rewrite)
{
    if (IsFileExists(dest) && rewrite == false) {
        return true;
    }
    QFile file{ source };
    return file.rename(dest);
}
