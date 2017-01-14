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

Light *LaserGenerator::get_lg_light(){
    return light;
}

void LaserGenerator::keyPressEvent(QKeyEvent *event){

    //左右方向键改变激光发射器的角度
    if(event->key()==Qt::Key_Left){
        if(this->laser_angle>=left_range){
            qDebug()<<"turn left";
            laser_angle-=2.5;
            this->setRotation(laser_angle);
            if(light){
                light->setRotation(laser_angle);
            }
        }
    }
    if(event->key()==Qt::Key_Right){
        if(this->laser_angle<=right_range){
            laser_angle+=2.5;
            this->setRotation(laser_angle);
            if(light){
                light->setRotation(laser_angle);
            }
        }
    }
    if(event->key()==Qt::Key_Escape){
            if(light){
            qDebug()<<"delete";
            scene()->removeItem(light);
            light=nullptr;
            mPressFlag_Space=false;
            }
    }

    //空格键发射激光
    if(event->key()==Qt::Key_Space){
        if(!mPressFlag_Space){
            light=new Light(QPoint(x()+5,y()+5),-laser_angle);
            qDebug()<<"Space_laser_angle"<<laser_angle;
            qDebug()<<"Light_angle"<<light->line().angle();
            scene()->addItem(light);
            //qDebug()<<"light?"<<!light;
            //qDebug()<<light->line().isNull();
            //qDebug()<<light->pen().width();
            //qDebug()<<scene();
            //qDebug()<<light->line().length();
            //qDebug()<<light->line().p1().x()<<light->line().p2().x();
            //qDebug()<<light->isVisible();
            //game->lights.append(new Light(QPoint(x()+5,y()),this->laser_angle));
            //game->lights.append(light);
            //qDebug()<<(game->lights);

            //play lasersound
            if(lasersound->state() == QMediaPlayer::PlayingState){
                lasersound->setPosition(0);
            }
            else if(lasersound->state() == QMediaPlayer::StoppedState){
                lasersound->play();
            }
            qDebug()<<"space";
            //不能再按space
            mPressFlag_Space=true;
        }
    }

}

/*
void LaserGenerator::keyReleaseEvent(QKeyEvent *event){
    if(event->key()==Qt::Key_Space &&light && !event->isAutoRepeat()){
        if(mPressFlag_Space){
            scene()->removeItem(light);
            delete light;
        }
        mPressFlag_Space =false;
    }
}
*/
