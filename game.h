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
    //private 函数接口
    Ball * get_ball();
    LaserGenerator *get_lasergenerator();
    Mirror * get_mirror();
    Win_Zone *get_win_zone();

    void write_ball(Ball *bl);
private:
    Ball *ball=nullptr;
    LaserGenerator *laserGenerator=nullptr;
    Mirror *mirror=nullptr;
    Win_Zone *win_zone=nullptr;
};

#endif // GAME_H
