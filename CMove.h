#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CMove.h"

#include "qdir.h"
#include "qfiledialog.h"
#include "qpushbutton.h"
#include "qtreeview.h"
#include "qfilesystemmodel.h"
#include "qstringlist.h"

#include "PathRepository.h"

class CMove : public QMainWindow
{
    Q_OBJECT

public:
    CMove(QWidget *parent = nullptr);
    ~CMove();

    QString GetDirByFileDialog(const QString& activePath);

signals:
    void onSourcePathChanged(const QString& path);
    void onDestinationPathChanged(const QString& path);

public slots:
    void OpenFileSourceDialog();
    void OpenFileDestinationDialog();

    void SaveSourcePath(const QString& path);
    void SaveDestinationPath(const QString& path);

    void SetSourcePathLineEdit(const QString& path);
    void SetDestinationPathLineEdit(const QString& path);

    void SetTreeView(const QString& path, const QString& filter);

private:
    Ui::CMoveClass ui;

    PathRepository pathRepository{ this };
};
