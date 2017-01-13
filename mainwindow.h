#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Settings.h"
#include "Loading.h"
#include "game.h"
#include <QMediaPlayer>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_Exit_clicked();
    void on_Settings_clicked();
    void on_StartGame_clicked();

private:
    Ui::MainWindow *ui;
    Settings *settings;
    Loading *loading;
    QMediaPlayer * bgm;
};

#endif // MAINWINDOW_H
