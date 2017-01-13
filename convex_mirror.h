#ifndef CONVEX_MIRROR_H
#define CONVEX_MIRROR_H
#include <QGraphicsPixmapItem>
#include <QPointF>
#include "Light.h"

class Convex_Mirror : public QGraphicsPixmapItem{
public:
    Convex_Mirror(QPointF p, double angle, double radius, double range);
    QPointF intersect(Light light);
    void reflect(Light light);
private:
    double angle;
    double range;
    double radius;
    QPointF focus_point;
};

#endif // CONVEX_MIRROR_H
