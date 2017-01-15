#include "Wall.h"

Wall::Wall(QPointF p1, QPointF p2){
    //this->setPixmap(QPixmap(":/images/wall.jpg"));
    this->setPos(p1);
    this->base_line=QLineF(p1,p2);
}

void Wall::absorb_light(Light light){
    //如果光线与墙有交点，墙把光线吸收
    if(light.line().intersect(this->base_line,nullptr)==1){
        QPointF p0 = *light.intersect_point(this->base_line);
        light.line().setP2(p0);
    }
}

