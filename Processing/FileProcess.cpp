#include "FileProcess.h"

FileProcess::FileProcess(QObject *parent)
	: QObject(parent)
{
}

FileProcess::~FileProcess()
{
}

bool FileProcess::StartTransaction(const TransactionParametres& params)
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

        if (IsTarget(srcName, params.FilterExpression)) {
            bool actionResult = this->MakeAction(params.Type, srcName, destName, params.Rewrite);
            if (!actionResult) {
                emit this->onOperationComplete();
                success = false;
            }
        }
    }

    QStringList dirs{ sourceDir.entryList(QDir::AllDirs | QDir::NoDotAndDotDot) };
    for (const QString& dir : dirs) {
        QString srcName = params.SourceFolder + QDir::separator() + dir;
        QString destName = params.DestinationFolder + QDir::separator() + dir;

        if (!IsDirContainsTargetFile(srcName, params.AnalisysResult->TargetFiles)) {
            continue;
        }

        TransactionParametres next{ params };
        next.SourceFolder = srcName;
        next.DestinationFolder = destName;

        success = this->StartTransaction(next);
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
    if (IsFileExists(dest) && rewrite == true) {
        QFile::remove(dest);
        return QFile::copy(source, dest);
    }
    return QFile::copy(source, dest);
}

const bool FileProcess::Move(const QString& source, const QString& dest, const bool rewrite)
{
    if (IsFileExists(dest) && rewrite == false) {
        return true;
    }
    if (IsFileExists(dest) && rewrite == true) {
        QFile::remove(dest);
        QFile file{ source };
        return file.rename(dest);
    }
    QFile file{ source };
    return file.rename(dest);
}

const bool FileProcess::IsDirContainsTargetFile(const QString& dirPath, const QStringList& targetFiles)
{
    QDir dir{ dirPath };
    QStringList dirFiles{ dir.entryList(QDir::Files) };
    for (const auto& file : dirFiles) {
        if (targetFiles.contains(file)) {
            return true;
        }
    }
    return false;
}

const bool FileProcess::IsTarget(const QString& file, const QString& filterExpression)
{
    return file.contains(filterExpression);
}

const bool FileProcess::MakeAction(const TransactionParametres::TransactionType type, const QString& src, const QString& dest, const bool rewrite)
{
    bool successFlag{ false };
    switch (type)
    {
    case TransactionParametres::TransactionType::Copy:
        successFlag = this->Copy(src, dest, rewrite);
        break;

    case TransactionParametres::TransactionType::Move:
        successFlag = this->Move(src, dest, rewrite);
        break;

    default:
        throw new std::exception("Uknown Operation");
    }
    return successFlag;
}