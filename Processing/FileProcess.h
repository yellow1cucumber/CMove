#pragma once

#include <QObject>
#include "qfile.h"
#include "qfileinfo.h"
#include "qdir.h"

#include "TransactionParametres.h"


class FileProcess : public QObject
{
	Q_OBJECT

public:
	FileProcess(QObject *parent);
	~FileProcess();

public slots:
	bool StartTransaction(TransactionParametres& params);

signals:
	void onOperationComplete();

private:
	const bool IsFileExists(const QString& file) const noexcept;
	const bool Copy(const QString& source, const QString& dest, const bool rewrite);
	const bool Move(const QString& source, const QString& dest, const bool rewrite);
};
