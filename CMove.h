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
#include "Validation/Validation.h"
#include "Settings/AppSettings.h"
#include "DirData/PathAnalisys.h"
#include "DirData/AnalisysResult.h"


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

    void onReadyToBuildTreeView(const QString& sourcePath, const QString& filter);
    void onReadyToAnalise(const QString& sourcePath, const QString& filter);

public slots:
    void OpenFileSourceDialog();
    void OpenFileDestinationDialog();

    void SaveSourcePath(const QString& path);
    void SaveDestinationPath(const QString& path);

    void SetSourcePathLineEdit(const QString& path);
    void SetDestinationPathLineEdit(const QString& path);

    void SetFilterExpression();
    
    void TryToBuildTreeView();

    void SetTreeView(const QString& path, const QString& filterInput);
    void AnalizeSource(const QString& path, const QString& filterExpression);

private:
    Ui::CMoveClass ui;
    PathAnalisys analisys{ this };
    Validation validator{ this };
    PathRepository pathRepository{ this };
    AppSettings settings{ this };

    void SetDefaultValues();

    bool isReadyToBuildTreeView();
    QStringList prepareFilter(const QString& filterInput);
};
