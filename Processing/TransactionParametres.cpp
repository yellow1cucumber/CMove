#include "TransactionParametres.h"

TransactionParametres::TransactionParametres(QObject* parent)
	: QObject{ parent }
{}

TransactionParametres::~TransactionParametres(){}

TransactionParametres::TransactionParametres(const TransactionParametres& other)
{
	this->setParent(other.parent());
	this->Rewrite = other.Rewrite;
	this->AnalisysResult = other.AnalisysResult;
	this->SourceFolder = other.SourceFolder;
	this->DestinationFolder = other.DestinationFolder;
	this->FilterExpression = other.FilterExpression;
	this->Type = other.Type;
}

const QString TransactionParametres::ToString() const
{
    auto toUtf16 = QStringDecoder(QStringDecoder::Utf8);

    QStringList rows{
        toUtf16("\tПараметры запуска\t"),
        QDateTime::currentDateTimeUtc().toString(),
        toUtf16("Исходная директория: ") + this->SourceFolder,
        toUtf16("Конечная директория: ") + this->DestinationFolder,
        toUtf16("Фильтр: ") + this->FilterExpression,
        toUtf16("Операция: ") + (
            this->Type == TransactionParametres::TransactionType::Copy ?
                toUtf16("копирование") :
                toUtf16("перемещение")),
        toUtf16("Перезапись: ") + (Rewrite ?
                toUtf16("да") :
                toUtf16("нет"))
    };
    return rows.join('\n');
}
