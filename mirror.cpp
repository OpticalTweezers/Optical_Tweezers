#include "mirror.h"
#include "Light.h"

Mirror::Mirror(QPointF p,QLineF l){
    setPixmap(QPixmap(":/images/mirror.jpg"));
    setPos(p);
    this->setRotation(l.angle());
    mid_point = (p+l.dx()*0.5,p+l.dy()*0.5);
}

Light Mirror::detect_light(){

}

void Mirror::reflect_light(Light light){
    light.reflect(mid_line);
}

