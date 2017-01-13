#include "Lasergenerator.h"
#include "game.h"
#include "light.h"
#include <QDebug>
#include <QMediaPlayer>
extern Game*game;
LaserGenerator::LaserGenerator(){
    setPixmap(QPixmap(":/images/laser_generator_2.png"));
    setPos(0,0);
    this->setTransformOriginPoint(70,70);
    laser_angle=0;
    lasersound = new QMediaPlayer();
    lasersound->setMedia(QUrl("qrc:/music/generate.wav"));
}

void LaserGenerator::keyPressEvent(QKeyEvent *event){

    //空格键发射激光
    if(event->key()==Qt::Key_Space){
        Light *light=new Light(QPoint(x()+5,y()),this->laser_angle);

        //game->lights.append(new Light(QPoint(x()+5,y()),this->laser_angle));
        //game->lights.append(light);
        //qDebug()<<(game->lights);

        scene()->addItem(light);
        //qDebug()<<"wushibinzuichou123";

        //play lasersound
        if(lasersound->state() == QMediaPlayer::PlayingState){
            lasersound->setPosition(0);
        }
        else if(lasersound->state() == QMediaPlayer::StoppedState){
            lasersound->play();
        }

    }

    //左右方向键改变激光发射器的角度
    else if(event->key()==Qt::Key_Left){
        laser_angle+=0.5;
        this->setRotation(laser_angle);
    }
    else if(event->key()==Qt::Key_Right){
        laser_angle-=0.5;
        this->setRotation(laser_angle);
    }

}

