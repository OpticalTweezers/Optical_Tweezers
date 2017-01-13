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

void LaserGenerator::set_range(double left, double right){
    this->left_range=left;
    this->right_range=right;
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
        if(this->laser_angle>=left_range){
            laser_angle+=2.5;
            this->setRotation(2.5);
        }
    }
    else if(event->key()==Qt::Key_Right){
        if(this->laser_angle<=right_range){
            laser_angle-=2.5;
            this->setRotation(-2.5);
        }
    }

}

