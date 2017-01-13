#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_stage1_clicked();
    void on_stage2_clicked();
    void on_stage3_clicked();
    void on_stage4_clicked();
    void on_stage5_clicked();
    void on_stage6_clicked();
    void on_stage7_clicked();
    void on_stage8_clicked();
    void on_stage9_clicked();
    void on_stage10_clicked();
    void on_stage11_clicked();
    void on_stage12_clicked();

    void on_backbutton_clicked();

private:
    Ui::Settings *ui;
};



#endif // SETTINGS_H
