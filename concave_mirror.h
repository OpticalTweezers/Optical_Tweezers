#ifndef CONCAVE_MIRROR_H
#define CONCAVE_MIRROR_H
#include <QGraphicsPixmapItem>
#include <QPointF>
#include "Light.h"

class Concave_Mirror : public QGraphicsPixmapItem{
public:
    Concave_Mirror(QPointF p, double angle, double radius, double range);
    QPointF intersect(Light light);
    void reflect(Light light);
private:
    double angle;
    double range;
    double radius;
    QPointF focus_point;
};

#endif // CONCAVE_MIRROR_H
