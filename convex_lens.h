#ifndef CONVEX_LENS_H
#define CONVEX_LENS_H
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <Light.h>

class Convex_Lens : public QGraphicsPixmapItem{
public:
    Convex_Mirror(QPointF p, double angle, double length, double focal_length);
    QPointF intersect(Light light);
    void refract(Light light);
private:
    double angle;
    double length;
    double focal_length;
    QPointF middle_point;
    QPointF focus_point;
    QLineF base_line;
    QLineF focal_line;
};
#endif // CONVEX_LENS_H
