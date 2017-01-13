#include "Concave_Lens.h"
#include <QtMath>

Concave_Lens::Concave_Lens(QPointF p, double angle, double length, double focal_length){
    //this->setPixmap(QPixmap(":/images/concave_lens"));
    this->middle_point=p;
    this->setPos(p.x()-(length/2),p.y());
    this->setTransformOriginPoint(p);
    this->setRotation(angle);
    this->angle=angle;
    this->length=length;
    this->focal_length=focal_length;
    this->focus_point=QPointF(p.x()-focal_length*qCos(angle),
                              p.y()-focal_length*qSin(angle));

    this->base_line = QLineF(p.x()-length*qSin(angle),p.y()+length*qCos(angle),
                             p.x()+length*qSin(angle),p.y()-length*qCos(angle));
    this->focal_line = QLineF(focus_point.x()-2000*qSin(angle),focus_point.y()+2000*qCos(angle),
                              focus_point.x()+2000*qSin(angle),focus_point.y()-2000*qCos(angle));
}

QPointF Concave_Lens::intersect(Light light){
    return light.intersect_point(base_line);
}

void Concave_Lens::refract(Light light){
    QPointF p0 = intersect(light);
    QPointF p1 = light.intersect_point(focal_line);
    double ang_ref = QLineF(p1,QPointF(0,0)).angle();
    Light *refract = new Light(p0,ang_ref);
    light.line().setP2(p0);
}
