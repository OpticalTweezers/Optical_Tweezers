#include "Loading.h"
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

//加载结束，关闭加载窗口，弹出游戏主界面
void Loading::finish(){
    this->hide();
    game.show();
    this->show();
}
