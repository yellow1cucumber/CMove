#pragma once

#include <QObject>

class PathRepository : public QObject
{
	Q_OBJECT

public:
	PathRepository(QObject *parent);
	~PathRepository();

	void SetSourcePath(QString path) noexcept;
	void SetDestinationPath(QString path) noexcept;

	QString* GetSourcePath() const noexcept;
	QString* GetDestinationPath() const noexcept;

private:
	QString SourcePath{ "" };
	QString DestinationPath{ "" };
};
