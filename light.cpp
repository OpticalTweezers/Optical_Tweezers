#include "light.h"
#include "game.h"
#include <qmath.h>
#include <QDebug>
#include <QPen>
extern Game*game;
Light::Light(QPointF p, double angle){
    QLineF line1;
    line1.setAngle(angle);
    line1.setP1(p);
    line1.setLength(2500);
    this->setLine(line1);
    qDebug()<<this->line().p1().x();
    qDebug()<<this->line().isNull();
    //this->line().setP2(QPointF(500,500));
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(10);
    this->setPen(pen);

    //this->reset_point_at_screen();

}
Light::Light(Light &light){
}



//求光线与固定线段的交点

QPointF Light::intersect_point(QLineF ln){
    double x0=this->line().p1().x();
    double y0=this->line().p2().y();
    double x1=ln.p1().x();
    double y1=ln.p2().y();
    double alpha=this->line().angle();
    double beta=ln.angle();
    if(this->line().intersect(ln,nullptr)){          //nullptr
    if(qTan(beta)!=qTan(alpha)){
        double x = y1-y0+x1*qTan(beta)-x0*qTan(alpha)/(qTan(beta)-qTan(alpha));
        double y = y0-qTan(alpha)*(x-x0);
        return QPoint(x,y);
    }
    else return QPointF(-1,-1);
    }
}

//求出光线与屏幕的交点
QPointF Light::intersect_screen(){
    qDebug()<<"sb";
    QLineF up(0,0,scene()->width(),0);
    QLineF down(0,scene()->height(),scene()->width(),scene()->height());
    QLineF left(0,0,0,scene()->height());
    QLineF right(scene()->width(),0,scene()->width(),scene()->height());
    qDebug()<<"this->line().intersect(down,nullptr)";
    if(this->line().intersect(up,nullptr)==2) return intersect_point(up);
    else if(this->line().intersect(down,nullptr)==2) return intersect_point(down);
    else if(this->line().intersect(left,nullptr)==2) return intersect_point(left);
    else if(this->line().intersect(right,nullptr)==2) return intersect_point(right);
    else return QPointF(-200,-200);
}

//重置终点为与屏幕的交点
void Light::reset_point_at_screen(){
    this->line().setP2(intersect_screen());
}


//光线与平面镜的反射
void Light::reflect(QLineF l){
    Light light(QPointF(0,0),0);
    if(this->line().intersect(l,nullptr)!=1) return ;  //If the class definition declares a move constructor or move assignment operator,
                                                            //the implicitly declared copy constructor is defined as deleted
    else {
        QPointF p=intersect_point(l);
        this->line().setP2(p);
        double alpha = this->line().angle();
        double beta = l.angle();
        double ref_angle;
        ref_angle = (2*beta-alpha)>360 ? (2*beta-alpha)-360:(2*beta-alpha);
        game->lights.append(new Light(p,ref_angle));
        scene()->addItem(game->lights[game->lights.size()-1]);
    }
}


