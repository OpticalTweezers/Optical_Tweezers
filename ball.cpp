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
    //initialazation
    velocity.setX(0);
    velocity.setY(0);
    acceleration.setX(0);
    acceleration.setY(0);

    QTimer *timer =new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100);
}

bool Ball::out_of_scene(){
    if(x()+pixmap().width()<0 ||x()>scene()->width()
        ||y()-pixmap().height()<0  ||y()>scene()->height())
        return true;
    else
        return false;
}

void Ball::move(){

    if(out_of_scene()){
        scene()->removeItem(this);
        delete this;
        return;
    }
    double dx=velocity.x();
    double dy=velocity.y();
    setPos(x()+dx,y()+dy);
}
void Ball::v_angel(){

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
