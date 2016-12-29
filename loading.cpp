#include "Loading.h"
#include "ui_loading.h"
#include <game.h>
#include <QTimer>
#include <QDebug>

Loading::Loading(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
    ui->progressBar->setRange(0,10);
    ui->progressBar->setValue(0);
    QTimer *timer=new QTimer();
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
    if(progressing==10){
        this->close();
        game=new Game();
        game->show();
        delete this;
    }
}






