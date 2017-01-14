#include "Concave_Mirror.h"
#include <QtMath>

Concave_Mirror::Concave_Mirror(QPointF p, double angle, double radius, double range){
    //this->setPixmap(QPixmap(":/images/concave_mirror"));
    this->setPos(p.x(),p.y());          //需要具体的数值
    this->setTransformOriginPoint(0,0); //需要具体的数值
    this->setRotation(angle);
    this->angle=angle;
    this->range=range;
    this->radius=radius;
    this->focus_point=QPointF(p.x(),p.y()); //需要具体的数值
}

QPointF Concave_Mirror::intersect(Light light){
    QPointF non_point_concave_mirror(-4,-4);
    double x0 = focus_point.x();
    double y0 = focus_point.y();
    double x1 = light.line().p1().x();
    double x2 = light.line().p2().x();
    double y1 = light.line().p1().y();
    double y2 = light.line().p2().y();
    if(x1==x2){
        if(radius*radius > (x1-x0)*(x1-x0)) return non_point_concave_mirror;
        else{
            double y3=y0+sqrt(radius*radius-(x1-x0)*(x1-x0));
            double y4=y0-sqrt(radius*radius-(x1-x0)*(x1-x0));
            QPointF p1(x1,y3);
            QPointF p2(x1,y4);
            QLineF l1(p1,this->focus_point);
            QLineF l2(p2,this->focus_point);
            if(l1.angle()>this->angle-this->range
                    && l1.angle()<this->angle+this->range)
                return p1;
            else if(l2.angle()>this->angle-this->range
                    && l2.angle()<this->angle+this->range)
                return p2;
            else return non_point_concave_mirror;
        }
    }
    else{
        double k = (y1-y2)/(x1-x2);
        double A = (k*k+1);
        double B = 2*(-x0-k*k*x1+k*y1-k*y0);
        double C = y1*y1+y0*y0+x0*x0+k*k*x1*x1-2*k*y1*x1+2*k*y0*x1-2*y1*y0-radius*radius;
        double delta = B*B-4*A*C;

        if(delta<=0) return non_point_concave_mirror;
        else{
            double x3 = (-B+sqrt(delta))/(2*A);
            double x4 = (-B+sqrt(delta))/(2*A);
            double y3 = y1+k*(x3-x1);
            double y4 = y1+k*(x4-x1);
            QPointF p1(x3,y3);
            QPointF p2(x4,y4);
            QLineF l1(p1,this->focus_point);
            QLineF l2(p2,this->focus_point);
            if(l1.angle()>this->angle-this->range
                    ||l1.angle()<this->angle+this->range)
                return p1;
            else if(l2.angle()>this->angle-this->range
                    ||l2.angle()<this->angle+this->range)
                return p2;
            else return non_point_concave_mirror;
        }
    }
}

void Concave_Mirror::reflect(Light light){
    QPointF p = intersect(light);
    light.line().setP2(p);
    double ang_ref = -QLineF(p,focus_point).angle();
    Light *reflect = new Light(p,ang_ref);
}
