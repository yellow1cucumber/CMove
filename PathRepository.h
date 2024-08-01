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

	QString GetSourcePath() const noexcept;
	QString GetDestinationPath() const noexcept;

signals:
	void onSourcePathChanged(const QString& newPath);
	void onDestinationPathChanged(const QString& newPath);

private:
	QString SourcePath{ "" };
	QString DestinationPath{ "" };
};
