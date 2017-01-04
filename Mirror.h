#ifndef MIRROR_H
#define MIRROR_H

#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QLineF>
#include "Light.h"

class Mirror : public QGraphicsPixmapItem{
public:
    Mirror(QPointF p, QLineF l);
    Light detect_light();
    void reflect_light(Light light);
private:
    QPointF mid_point;
    QLineF mid_line;
};

#endif // MIRROR_H
