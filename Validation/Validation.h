#pragma once

#include <QObject>

#include "qdir.h"

class Validation : public QObject
{
	Q_OBJECT

public:
	Validation(QObject *parent);
	~Validation();

	bool IsPathExists(const QString& path) const noexcept;
	bool IsReadyToProcess(const QString& sourcePath,
						  const QString& destPath) const noexcept;

	void SetFilterExpression(QString filterExpression) noexcept;
	QString GetFilterExpression() const noexcept;

signals:
	void onFilterExpressionChanged(const QString& filterExpression);

private:
	QString filterExpression{ "" };
};
