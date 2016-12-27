#include "loading.h"
#include "ui_loading.h"
#include <QTimer>
#include <QProgressBar>

Loading::Loading(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Loading)
{
    ui->setupUi(this);
}

Loading::~Loading(){
    delete ui;
}

void Loading::progress_move(){
    for(int i=0;i<=100;i++){
        for(int j=0;j<=1000000;j++){
            ui->progressBar->setValue(i);
        }
    }
}

void Loading::finish(){
    this->hide();
    maingame.show();
    this->show();
}
