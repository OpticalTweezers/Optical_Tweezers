#ifndef GAME3_H
#define GAME3_H

#include "game.h"

class Game3:public Game{
public:
    Game3();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};

#endif // GAME3_H
