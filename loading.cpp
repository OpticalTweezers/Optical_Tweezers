#include "Loading.h"
#include "ui_loading.h"
#include <game.h>
#include <QTimer>
#include <QDebug>
Game*game;
Loading::Loading(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,1);
    ui->progressBar->setValue(0);
    timer=new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(progressing_change()));
    timer->start(300);
}
Loading::~Loading(){
    delete ui;
}

void Loading::progressing_change(){
    progressing++;
    ui->progressBar->setValue(progressing);
    qDebug()<<progressing;
    if(progressing==1){
        this->close();
        game=new Game();
        game->show();
        qDebug()<<game->scene->width();
        timer->stop();
    }
}

void Loading::on_pushButton_clicked()
{

}






