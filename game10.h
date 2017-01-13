#ifndef GAME10_H
#define GAME10_H

#include "game.h"

class Game10:public Game{
public:
    Game10();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME10_H
