#ifndef GAME9_H
#define GAME9_H

#include "game.h"

class Game9:public Game{
public:
    Game9();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME9_H
