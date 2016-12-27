#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "loading.h"

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

void MainWindow::on_Exit_clicked(){
    QApplication::closeAllWindows();
}

void MainWindow::on_Settings_clicked(){
    this->hide();
    settings.show();
    settings.exec();
    this->show();
}

void MainWindow::on_StartGame_clicked(){
    this->hide();
    loading.show();
    loading.progress_move();
}
