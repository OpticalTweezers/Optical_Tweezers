#include <Ball.h>
#include <game.h>
#include <QPainter>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QtMath>

extern Game *game;
Ball::Ball(QGraphicsItem *parent):QObject(),QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/Ball.png"));
    setPos(400,300);
    //initialazation
    velocity.setX(10);
    velocity.setY(10);
    acceleration.setX(0);
    acceleration.setY(0);

    QVector2D F(0,10);
    qDebug()<<3;
    QTimer *timer_a =new QTimer();
    qDebug()<<2333;
    connect(timer_a,SIGNAL(timeout()),this,SLOT(v_change(F)));
    timer_a->start(100);

    QTimer *timer_v =new QTimer();
    connect(timer_v,SIGNAL(timeout()),this,SLOT(move()));
    timer_v->start(100);


}
//判断出屏幕
bool Ball::out_of_scene(){
    if(x()+pixmap().width()<0 ||x()>scene()->width()
        ||y()-pixmap().height()<0  ||y()>scene()->height())
        return true;
    else
        return false;
}
//ball运动
void Ball::move(){

    if(out_of_scene()){
        scene()->removeItem(this);
        delete this;
        qDebug()<<"gameover";
        return;
    }
    double dx=velocity.x();
    double dy=velocity.y();
    setPos(x()+dx,y()+dy);
    //qDebug()<<3;
}

//ball受力改变velocity
void Ball::v_change(QVector2D force){
    velocity.setX(velocity.x()+force.x());
    velocity.setY(velocity.y()+force.y());
    qDebug()<<velocity.x();
}

/*     Non_use
void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPainterPath path;
    path.addEllipse(pixmap().width()/2,pixmap().height()/2,30,30);
    painter->setClipPath(path);
    painter->drawPixmap(QPointF(pixmap().width()/2,pixmap().height()/2),my_pixmap);
    qDebug() <<"2333333";
}
    用painter来截取path的废代码
*/
