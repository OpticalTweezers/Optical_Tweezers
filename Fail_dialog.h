#ifndef FAIL_DIALOG_H
#define FAIL_DIALOG_H

#include <QDialog>

namespace Ui {
class Fail_dialog;
}

class Fail_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Fail_dialog(QWidget *parent = 0);
    ~Fail_dialog();

private:
    Ui::Fail_dialog *ui;
};

#endif // FAIL_DIALOG_H
