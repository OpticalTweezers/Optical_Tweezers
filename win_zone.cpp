#include <QPointF>
#include <QList>
#include <win_zone.h>
#include <Win_dialog.h>
#include <game.h>
#include <QDebug>
#include <QTimer>
Win_Zone::Win_Zone(){
    QPointF center(700,400);
    double width=100;
    double height=100;
    this->setPos(center.x()-width*0.5,center.y()-height*0.5);
    this->setPixmap(QPixmap(":/images/win_zone.png"));
    timer =new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(detect_ball()));
    timer->start(50);
}

void Win_Zone::detect_ball(){
    QList<QGraphicsItem*> colliding_Items=collidingItems();
    for (int i=0;i<colliding_Items.size();i++){
        Ball *ball_in_zone =dynamic_cast<Ball *>(colliding_Items[i]);
        if(ball_in_zone){
            //qDebug()<<"win_dialog_show";
            win_dialog=new Win_dialog();
            win_dialog->show();
            timer->stop();
        }
    }
}

