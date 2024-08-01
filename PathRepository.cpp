#include "PathRepository.h"

PathRepository::PathRepository(QObject *parent)
	: QObject(parent)
{
}

PathRepository::~PathRepository()
{
}

void PathRepository::SetSourcePath(QString path) noexcept 
{
	this->SourcePath = path;
	emit this->onSourcePathChanged(this->SourcePath);
}

void PathRepository::SetDestinationPath(QString path) noexcept
{
	this->DestinationPath = path;
	emit this->onDestinationPathChanged(this->DestinationPath);
}

QString PathRepository::GetSourcePath() const noexcept
{
	return this->SourcePath;
}

QString PathRepository::GetDestinationPath() const noexcept
{
	return this->SourcePath;
}
