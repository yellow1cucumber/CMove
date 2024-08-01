#include "CMove.h"

CMove::CMove(QWidget *parent)
    : QMainWindow(parent)
{
    this->ui.setupUi(this);

    this->connect(this->ui.SelectSourcePathButton, &QPushButton::clicked, 
                  this, &CMove::OpenFileSourceDialog);
    this->connect(this->ui.SelectDestinationPathButton, &QPushButton::clicked,
                  this, &CMove::OpenFileDestinationDialog);
}

CMove::~CMove()
{}

QString CMove::GetDirByFileDialog()
{
    QString dir = QFileDialog::getExistingDirectory(
        this,
        tr("Source directory"),
        "C:",
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

void CMove::SetSourcePath(const QString& path) {
    this->pathRepository.SetSourcePath(path);
}
void CMove::SetDestinationPath(const QString& path) {
    this->pathRepository.SetDestinationPath(path);
}
#pragma endregion
