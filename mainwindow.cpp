#include "Mainwindow.h"
#include "ui_mainwindow.h"
#include "Settings.h"
#include "Loading.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PhysicsGame->setStyleSheet("color:darkblue;");
}

MainWindow::~MainWindow(){
    delete ui;
}

//点击退出键，关闭所有窗口
void MainWindow::on_Exit_clicked(){
    QApplication::closeAllWindows();
}

//点击设置键，弹出设置窗口
void MainWindow::on_Settings_clicked(){
    this->hide();
    settings.show();
    settings.exec();
    this->show();
}

//点击开始游戏键，弹出加载游戏窗口
void MainWindow::on_StartGame_clicked(){
    this->hide();
    loading.show();
    loading.progress_move();
}
