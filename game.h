#ifndef GAME_H
#define GAME_H
#include <Ball.h>
#include <light.h>
#include <lasergenerator.h>
#include <Mirror.h>
#include <win_zone.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
#include <QVector>
class Game:public QGraphicsView{
public:
    Game();
    QGraphicsScene *scene;
    QVector<Light*>lights;
private:
    Ball *ball;
    LaserGenerator *laserGenerator;
    Mirror *mirror;
    Win_Zone *win_zone;
};

#endif // GAME_H
