#include "CMove.h"

CMove::CMove(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui.setupUi(this);

    this->SetDefaultValues();

    this->connect(this->ui.SelectSourcePathButton, &QPushButton::clicked, 
                  this, &CMove::OpenFileSourceDialog);
    this->connect(this->ui.SelectDestinationPathButton, &QPushButton::clicked,
                  this, &CMove::OpenFileDestinationDialog);

    this->connect(this, &CMove::onSourcePathChanged,
                  this, &CMove::SaveSourcePath);
    this->connect(this, &CMove::onDestinationPathChanged,
                  this, &CMove::SaveDestinationPath);

    this->connect(&this->pathRepository, &PathRepository::onSourcePathChanged,
                  this, &CMove::SetSourcePathLineEdit);
    this->connect(&this->pathRepository, &PathRepository::onDestinationPathChanged,
                  this, &CMove::SetDestinationPathLineEdit);

    this->connect(this->ui.SourcePathLineEdit, &QLineEdit::textChanged,
                  this, &CMove::SaveSourcePath);
    this->connect(this->ui.DestinationPathLineEdit, &QLineEdit::textChanged,
                  this, &CMove::SaveDestinationPath);

    this->connect(this->ui.RegexLineEdit, &QLineEdit::editingFinished,
                  this, &CMove::SetFilterExpression);

    this->connect(this, &CMove::onReadyToBuildTreeView,
                  this, &CMove::SetTreeView);
    this->connect(this, &CMove::onReadyToAnalise,
                  this, &CMove::AnalizeSource);

    this->connect(&this->pathRepository, &PathRepository::onSourcePathChanged,
                  this, &CMove::TryToBuildTreeView);
    this->connect(&this->validator, &Validation::onFilterExpressionChanged,
                  this, &CMove::TryToBuildTreeView);

    this->connect(this->ui.StartButton, &QPushButton::clicked,
                  this, &CMove::TryToStart);
    this->connect(this, &CMove::onReadyToProcess,
                  &this->processor, &FileProcess::StartTransaction);
}

CMove::~CMove()
{}

QString CMove::GetDirByFileDialog(const QString& activePath)
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Source directory"),
        activePath,
        QFileDialog::DontResolveSymlinks
        );
    return dir;
}

bool CMove::isReadyToBuildTreeView()
{
    if (this->pathRepository.GetSourcePath().isEmpty() ||
        this->validator.GetFilterExpression().isEmpty()) 
    {
        return false;
    }
    return true;
}

QStringList CMove::prepareFilter(const QString& filterInput)
{
    QStringList filter;
    QString filterExpression{ filterInput };
    filterExpression = "*" + filterExpression + "*";
    filter << filterExpression;
    return filter;
}

void CMove::SetDefaultValues() {
    this->settings.params.beginGroup("Default");
    const auto filterExpressionDefault =
        this->settings.params.value("FilterExpressionDefault", QString{""}).toString();
    this->ui.RegexLineEdit->setText(filterExpressionDefault);
    this->validator.SetFilterExpression(filterExpressionDefault);
}


#pragma region Slots
void CMove::OpenFileSourceDialog() {
    QString activePath{ "" };
    this->pathRepository.GetSourcePath().isEmpty() ?
        activePath = QString::fromUtf8("C:/") :
        activePath = this->pathRepository.GetSourcePath().toUtf8();

    QString dir = this->GetDirByFileDialog(activePath);
    emit onSourcePathChanged(dir);
}
void CMove::OpenFileDestinationDialog() {
    QString activePath{ "" };
    this->pathRepository.GetDestinationPath().isEmpty() ?
        activePath = QString::fromUtf8("C:/") :
        activePath = this->pathRepository.GetDestinationPath().toUtf8();
    
    QString dir = this->GetDirByFileDialog(activePath);
    emit onDestinationPathChanged(dir);
}

void CMove::SaveSourcePath(const QString& path) {
    this->pathRepository.SetSourcePath(path);
}
void CMove::SaveDestinationPath(const QString& path) {
    this->pathRepository.SetDestinationPath(path);
}

void CMove::SetSourcePathLineEdit(const QString& path) {
    this->ui.SourcePathLineEdit->setText(path);
}
void CMove::SetDestinationPathLineEdit(const QString& path) {
    this->ui.DestinationPathLineEdit->setText(path);
}

void CMove::SetFilterExpression()
{
    auto filterExpression = this->ui.RegexLineEdit->text();
    this->validator.SetFilterExpression(filterExpression);
}

void CMove::TryToBuildTreeView()
{
    if (isReadyToBuildTreeView()) {
        emit onReadyToBuildTreeView(this->pathRepository.GetSourcePath(),
                                    this->validator.GetFilterExpression());
        emit onReadyToAnalise(this->pathRepository.GetSourcePath(),
                              this->validator.GetFilterExpression());
    }
}

void CMove::SetTreeView(const QString& path, const QString& filterInput) {
    auto model = new QFileSystemModel(this);
    model->setRootPath(path + "/");
    model->setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::AllDirs);
    auto filter = this->prepareFilter(filterInput);
    model->setNameFilters(filter);
    model->setNameFilterDisables(false);
    this->ui.FilesTreeView->setModel(model);
    this->ui.FilesTreeView->setRootIndex(model->index(path + "/"));
    this->connect(model, &QFileSystemModel::directoryLoaded,
                  this->ui.FilesTreeView, &QTreeView::expandAll);
}
void CMove::AnalizeSource(const QString& path, const QString& filterExpression)
{
    AnalisysResult* res = &this->analisys.Analize(path, filterExpression);
    QString totalFiles = QString::number(res->GetFoundFilesCount());
    QString filesByFilterExpression = QString::number(res->GetFilesByRegexCount());
    QString subdirs = QString::number(res->GetFoundSubdirsCount());

    this->ui.FilesTotalLineEdit->setText(totalFiles);
    this->ui.FilesByFilterLineEdit->setText(filesByFilterExpression);
    this->ui.SubdirsLineEdit->setText(subdirs);
}

void CMove::TryToStart()
{
    QString source{ this->pathRepository.GetSourcePath() };
    QString dest{ this->pathRepository.GetDestinationPath() };

    if (!validator.IsReadyToProcess(source, dest)) {
        QMessageBox::warning(this, tr("Warning"), tr("Check source and destination paths"), QMessageBox::Ok);
        return;
    }

    QString filterExpression{ this->validator.GetFilterExpression() };
    bool rewriteFlag = this->ui.ReplaceRadioButton->isChecked();
    bool moveFlag = this->ui.MoveRadioButton->isChecked();


    TransactionParametres params;
    params.SourceFolder = source;
    params.DestinationFolder = dest;
    params.FilterExpression = filterExpression;
    params.Rewrite = rewriteFlag;
    params.AnalisysResult = &this->analisys.Result;
    moveFlag ?
        params.Type = TransactionParametres::TransactionType::Move :
        params.Type = TransactionParametres::TransactionType::Copy ;

    emit onReadyToProcess(params);
}

#pragma endregion
