#include "Win_Zone.h"
#include <QPointF>


Win_Zone::Win_Zone(QPointF center ,double width,double height){
    this->setPos(center.x()-width*0.5,center.y()-height*0.5);
    this->setPixmap(QPixmap(":/images/win_zone.jpg"));
}
