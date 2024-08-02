#include "TransactionParametres.h"

TransactionParametres::TransactionParametres(QObject* parent)
	: QObject{ parent }
{}

TransactionParametres::~TransactionParametres(){}

TransactionParametres::TransactionParametres(const TransactionParametres& other)
{
	this->setParent(other.parent());
	this->Rewrite = other.Rewrite;
	this->SourceFolder = other.SourceFolder;
	this->DestinationFolder = other.DestinationFolder;
	this->Type = other.Type;
}