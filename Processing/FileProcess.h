#pragma once

#include <QObject>
#include "qfile.h"
#include "qfileinfo.h"
#include "qdir.h"
#include <exception>

#include "TransactionParametres.h"


class FileProcess : public QObject
{
	Q_OBJECT

public:
	FileProcess(QObject *parent);
	~FileProcess();

public slots:
	bool StartTransaction(const TransactionParametres& params);

signals:
	void onOperationComplete();

private:
	const bool IsFileExists(const QString& file) const noexcept;
	const bool IsTarget(const QString& file, const QString& filterExpression);
	const bool MakeAction(const TransactionParametres::TransactionType type, const QString& src, const QString& dest, const bool rewrite);
	const bool Copy(const QString& source, const QString& dest, const bool rewrite);
	const bool Move(const QString& source, const QString& dest, const bool rewrite);
	const bool IsDirContainsTargetFile(const QString& dir, const QStringList& targetFiles);
};
