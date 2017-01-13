#ifndef GAME11_H
#define GAME11_H

#include "game.h"

class Game11:public Game{
public:
    Game11();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME11_H
