#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CMove.h"

#include "qdir.h"
#include "qfiledialog.h"
#include "qpushbutton.h"

#include "PathRepository.h"

class CMove : public QMainWindow
{
    Q_OBJECT

public:
    CMove(QWidget *parent = nullptr);
    ~CMove();

    QString GetDirByFileDialog();

signals:
    void onDestinationPathSelected(const QString& path);
    void onSourcePathSelected(const QString& path);

public slots:
    void OpenFileSourceDialog();
    void OpenFileDestinationDialog();

    void SetSourcePath(const QString& path);
    void SetDestinationPath(const QString& path);

private:
    Ui::CMoveClass ui;

    PathRepository pathRepository{ this };
};
