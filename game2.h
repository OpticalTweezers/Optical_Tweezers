#ifndef GAME2_H
#define GAME2_H

#include "game.h"

class Game2:public Game{
public:
    Game2();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
};


#endif // GAME2_H
