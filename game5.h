#ifndef GAME5_H
#define GAME5_H

#include "game.h"

class Game5:public Game{
public:
    Game5();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME5_H
