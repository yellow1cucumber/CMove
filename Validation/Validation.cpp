#include "Validation.h"

Validation::Validation(QObject *parent)
	: QObject(parent)
{
}

Validation::~Validation()
{
}

bool Validation::IsPathExists(const QString& path) const noexcept
{
	if (QDir{ path }.exists()) {
		return true;
	}
	return false;
}

bool Validation::IsReadyToProcess(const QString& sourcePath, 
								  const QString& destPath) const noexcept
{
	if (IsPathExists(sourcePath) && IsPathExists(destPath)) {
		return true;
	}
	return false;
}

void Validation::SetFilterExpression(QString filterExpression) noexcept
{
	this->filterExpression = filterExpression;
	emit this->onFilterExpressionChanged(this->filterExpression);
}

QString Validation::GetFilterExpression() const noexcept
{
	return this->filterExpression;
}
