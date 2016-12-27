#include "lasergenerator.h"
#include "game.h"
#include "light.h"

LaserGenerator::LaserGenerator(){
    setPixmap(QPixmap(":/image/laser-generator.jpg"));
    setPos(0,0);
    this->setTransformOriginPoint(5,1);
    laser_angle=0;
}

void LaserGenerator::keyPressEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Space){
        Light *light=new Light(QPoint(x()+5,y()),this->laser_angle);
        scene()->addItem(light);
    }
    else if(event->key()==Qt::Key_Left){
        laser_angle+=2.5;
        this->setRotation(2.5);
    }
    else if(event->key()==Qt::Key_Right){
        laser_angle-=2.5;
        this->setRotation(-2.5);
    }

}

