#include "mirror.h"
#include "Light.h"
#include <QTimer>
#include "game.h"
extern Game*game;
Mirror::Mirror(QLineF l){
    setPixmap(QPixmap(":/images/mirror.jpg"));
    setPos(l.p1());
    this->mid_line = l;
    this->mid_point = QPointF(0.5*(l.p1().x()+l.p2().x()),
                              0.5*(l.p1().y()+l.p2().y()));
    this->setTransformOriginPoint(mid_point);
    this->setRotation(l.angle());
    qDebug()<<"mirror";

    QTimer *timer =new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(reflect_light()));
    timer->start(100);
}

void Mirror::reflect(Light *lt){
    if(mid_line.intersect(lt->line(),nullptr)!=1){   //If the class definition declares a move constructor or move assignment operator,
        qDebug()<<mid_line;
        qDebug()<<"enter reflect";
        return ;
    }                                                            //the implicitly declared copy constructor is defined as deleted
    else {
        QPointF p=*lt->intersect_point(mid_line);
        QLineF reflected_light_line(lt->line().p1(),p) ;
        game->get_lasergenerator()->get_lg_light()->setLine(reflected_light_line);
        double alpha = lt->line().angle();
        double beta = mid_line.angle();
        double ref_angle;
        ref_angle = (2*beta-alpha)>360 ? (2*beta-alpha)-360:(2*beta-alpha);
        mirror_reflected_light.append(new Light(p,ref_angle));
        int index=mirror_reflected_light.size()-1;
        scene()->addItem(mirror_reflected_light[index]);
    }
}


void Mirror::reflect_light(){
    if(game->get_lasergenerator()->get_lg_light()){
        qDebug()<<"reflect?";
        for(int i=0;i<mirror_reflected_light.size();i++){
            scene()->removeItem(mirror_reflected_light[i]);
        }
        mirror_reflected_light.clear();
        reflect(game->get_lasergenerator()->get_lg_light());
    }

}

void Mirror::rotate(double rotate_angle){
    this->setRotation(rotate_angle);
    QLineF line1 = QLineF(mid_point,mid_line.p1());
    line1.setAngle(line1.angle()+rotate_angle);
    QLineF line2 = QLineF(mid_point,mid_line.p2());
    line2.setAngle(line2.angle()+rotate_angle);
    mid_line.setP1(line1.p2());
    mid_line.setP2(line2.p2());
}

