#include "Mainwindow.h"
#include "ui_mainwindow.h"
#include "Settings.h"
#include "Loading.h"
#include <QDebug>
#include <QMediaPlayer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->PhysicsGame->setStyleSheet("color:red");
    bgm = new QMediaPlayer();
    bgm->setMedia(QUrl("qrc:/music/mainwindow_bgm.mp3"));
    bgm->play();
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
    settings=new Settings();
    this->hide();
    settings->show();
}

//点击开始游戏键，弹出加载游戏窗口
void MainWindow::on_StartGame_clicked(){
    loading=new Loading();
    this->hide();
    loading->show();
}
