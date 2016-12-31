#include "Lasergenerator.h"
#include "game.h"
#include "light.h"
extern Game*game;
LaserGenerator::LaserGenerator(){
    setPixmap(QPixmap(":/images/laser_generator.jpg"));
    setPos(0,0);
    this->setTransformOriginPoint(5,1);
    laser_angle=0;
}

void LaserGenerator::keyPressEvent(QKeyEvent *event){

    //空格键发射激光
    if(event->key()==Qt::Key_Space){
        game->lights.append(new Light(QPoint(x()+5,y()),this->laser_angle));
        scene()->addItem(game->lights[0]);
    }

    //左右方向键改变激光发射器的角度
    else if(event->key()==Qt::Key_Left){
        laser_angle+=2.5;
        this->setRotation(2.5);
    }
    else if(event->key()==Qt::Key_Right){
        laser_angle-=2.5;
        this->setRotation(-2.5);
    }

}

