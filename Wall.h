#ifndef WALL_H
#define WALL_H
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QLineF>
#include <Light.h>

class Wall : public QGraphicsPixmapItem{
public:
    Wall(QPointF p1,QPointF p2);
    void absorb_light(Light light);
private:
    QLineF base_line;
};

#endif // WALL_H
