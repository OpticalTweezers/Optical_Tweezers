#ifndef GAME6_H
#define GAME6_H

#include "game.h"

class Game6:public Game{
public:
    Game6();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME6_H
