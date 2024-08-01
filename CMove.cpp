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
#pragma endregion
