#ifndef GAME7_H
#define GAME7_H

#include "game.h"

class Game7:public Game{
public:
    Game7();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME7_H
