#include "Fail_dialog.h"
#include "ui_fail_dialog.h"

Fail_dialog::Fail_dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Fail_dialog)
{
    ui->setupUi(this);
}

Fail_dialog::~Fail_dialog()
{
    delete ui;
}
