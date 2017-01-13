#ifndef GAME12_H
#define GAME12_H

#include "game.h"

class Game12:public Game{
public:
    Game12();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME12_H
