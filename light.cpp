#include "light.h"
#include "game.h"
#include <qmath.h>

Light::Light(QPointF p, double angle){
    this->line().setAngle(angle);
    this->line().setP1(p);
    this->line().setLength(2500);
}

Light::Light(QLineF line){
    this->setLine(line);
}

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

QPointF Light::intersect_screen(){
    QLineF up(0,0,scene()->width(),0);
    QLineF down(0,scene()->height(),scene()->width(),scene()->height());
    QLineF left(0,0,0,scene()->height());
    QLineF right(scene()->width(),0,scene()->width(),scene()->height());
    if(this->line().intersect(up,nullptr)==2) return intersect_point(up);
    else if(this->line().intersect(down,nullptr)==2) return intersect_point(down);
    else if(this->line().intersect(left,nullptr)==2) return intersect_point(left);
    else if(this->line().intersect(right,nullptr)==2) return intersect_point(right);
    else return QPointF(-200,-200);
}

void Light::reset_point_at_screen(){

}
