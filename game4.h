#ifndef GAME4_H
#define GAME4_H

#include "game.h"

class Game4:public Game{
public:
    Game4();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME4_H
