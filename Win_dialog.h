#ifndef WIN_DIALOG_H
#define WIN_DIALOG_H

#include <QDialog>

namespace Ui {
class Win_dialog;
}

class Win_dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Win_dialog(QWidget *parent = 0);
    ~Win_dialog();

private:
    Ui::Win_dialog *ui;
};

#endif // WIN_DIALOG_H
