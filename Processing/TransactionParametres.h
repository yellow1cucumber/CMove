#include <QtCore>

struct TransactionParametres {
	enum class TransactionType
	{
		Copy,
		Move
	};

	bool Rewrite{ false };
	QString SourceFolder{ "" };
	QString DestinationFolder{ "" };
	TransactionParametres::TransactionType Type;
};
