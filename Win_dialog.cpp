#include "Win_dialog.h"
#include "ui_win_dialog.h"

Win_dialog::Win_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Win_dialog)
{
    ui->setupUi(this);
}

Win_dialog::~Win_dialog()
{
    delete ui;
}
