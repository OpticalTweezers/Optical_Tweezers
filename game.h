#ifndef GAME_H
#define GAME_H
#include <Ball.h>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QBrush>
class Game:public QGraphicsView{
public:
    Game();
    QGraphicsScene *scene;
private:
};

#endif // GAME_H
