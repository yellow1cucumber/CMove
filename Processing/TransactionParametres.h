#pragma once

#include "qobject.h"
#include "../DirData/AnalisysResult.h"

class TransactionParametres : QObject
{
	Q_OBJECT

public:
	TransactionParametres(QObject* parent = nullptr);
	~TransactionParametres();

	TransactionParametres(const TransactionParametres& other);

	enum class TransactionType
	{
		Copy,
		Move
	};

	const QString ToString() const;

	AnalisysResult* AnalisysResult{ nullptr };
	bool Rewrite{ false };
	QString SourceFolder{ "" };
	QString DestinationFolder{ "" };
	QString FilterExpression{ "" };
	TransactionParametres::TransactionType Type{ TransactionParametres::TransactionType::Move };
};
