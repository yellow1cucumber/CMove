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
}

void PathRepository::SetDestinationPath(QString path) noexcept
{
	this->DestinationPath = path;
}

QString* PathRepository::GetSourcePath() const noexcept
{
	return nullptr;
}

QString* PathRepository::GetDestinationPath() const noexcept
{
	return nullptr;
}
