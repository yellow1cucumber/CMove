#include "CMove.h"

CMove::CMove(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui.setupUi(this);

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
    if (isReadyToBuildTreeView()) {
        emit onReadyToBuildTreeView(this->pathRepository.GetSourcePath(),
                                    this->validator.GetFilterExpression());
    }
}
void CMove::SaveDestinationPath(const QString& path) {
    this->pathRepository.SetDestinationPath(path);
}

void CMove::SetSourcePathLineEdit(const QString& path) {
    this->ui.SourcePathLineEdit->setText(path);
    if (isReadyToBuildTreeView()) {
        emit onReadyToBuildTreeView(this->pathRepository.GetSourcePath(),
                                    this->validator.GetFilterExpression());
    }
}
void CMove::SetDestinationPathLineEdit(const QString& path) {
    this->ui.DestinationPathLineEdit->setText(path);
}

void CMove::SetFilterExpression()
{
    auto filterExpression = this->ui.RegexLineEdit->text();
    this->validator.SetFilterExpression(filterExpression);
    if (isReadyToBuildTreeView()) {
        emit onReadyToBuildTreeView(this->pathRepository.GetSourcePath(), 
                                    this->validator.GetFilterExpression());
    }
}

void CMove::SetTreeView(const QString& path, const QString& filterInput) {
    auto model = new QFileSystemModel(this);
    model->setRootPath(path + "/");
    model->setFilter(QDir::Files | QDir::NoDotAndDotDot);
    auto filter = this->prepareFilter(filterInput);
    model->setNameFilters(filter);
    model->setNameFilterDisables(false);
    this->ui.FilesTreeView->setModel(model);
}
#pragma endregion
