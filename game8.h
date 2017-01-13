#ifndef GAME8_H
#define GAME8_H

#include "game.h"

class Game8:public Game{
public:
    Game8();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME8_H
