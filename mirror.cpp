#include "mirror.h"
#include "Light.h"

Mirror::Mirror(QLineF l){
    setPixmap(QPixmap(":/images/mirror.jpg"));
    setPos(l.p1());
    this->mid_line = l;
    this->mid_point = QPointF(0.5*(l.p1().x()+l.p2().x()),
                              0.5*(l.p1().y()+l.p2().y()));
    this->setTransformOriginPoint(mid_point);
    this->setRotation(l.angle());
}

Light Mirror::detect_light(){

}

void Mirror::reflect_light(Light light){
    light.reflect(mid_line);
}

void Mirror::rotate(double rotate_angle){
    this->rotate(rotate_angle);
    QLineF tmp = QLineF(mid_point,mid_line.p1());
    tmp.setAngle(tmp.angle()+rotate_angle);
    mid_line.setAngle(mid_line.angle()+rotate_angle);
    mid_line.setP1(tmp.p2());
}

