#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CMove.h"

#include "PathRepository.h"

class CMove : public QMainWindow
{
    Q_OBJECT

public:
    CMove(QWidget *parent = nullptr);
    ~CMove();

private:
    Ui::CMoveClass ui;

    PathRepository pathRepository;
};
