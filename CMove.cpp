#include "CMove.h"

CMove::CMove(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui.setupUi(this);

    this->connect(this->ui.SelectSourcePathButton, &QPushButton::clicked, 
                  this, &CMove::OpenFileSourceDialog);
    this->connect(this->ui.SelectDestinationPathButton, &QPushButton::clicked,
                  this, &CMove::OpenFileDestinationDialog);

    this->connect(this, &CMove::onSourcePathSelected,
                  this, &CMove::SaveSourcePath);
    this->connect(this, &CMove::onDestinationPathSelected,
                  this, &CMove::SaveDestinationPath);

    this->connect(&this->pathRepository, &PathRepository::onSourcePathChanged,
                  this, &CMove::SetSourcePathLineEdit);
    this->connect(&this->pathRepository, &PathRepository::onDestinationPathChanged,
                  this, &CMove::SetDestinationPathLineEdit);
}

CMove::~CMove()
{}

QString CMove::GetDirByFileDialog()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Source directory"),
        "C:/",
        QFileDialog::DontResolveSymlinks
        );
    return dir;
}


#pragma region Slots
void CMove::OpenFileSourceDialog() {
    QString dir = this->GetDirByFileDialog();
    emit onSourcePathSelected(dir);
}
void CMove::OpenFileDestinationDialog() {
    QString dir = this->GetDirByFileDialog();
    emit onDestinationPathSelected(dir);
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
