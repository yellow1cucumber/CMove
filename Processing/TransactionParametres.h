#pragma once

#include "qobject.h"


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

	bool Rewrite{ false };
	QString SourceFolder{ "" };
	QString DestinationFolder{ "" };
	TransactionParametres::TransactionType Type{ TransactionParametres::TransactionType::Move };
};
