#ifndef CONCAVE_LENS_H
#define CONCAVE_LENS_H
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <Light.h>

class Concave_Lens : public QGraphicsPixmapItem{
public:
    Concave_Mirror(QPointF p, double angle, double length, double focal_length);
    QPointF intersect(Light light);
    void refract(Light light);
private:
    double angle;       //angle指向焦点的反方向
    double length;
    double focal_length;
    QPointF middle_point;
    QPointF focus_point;
    QLineF base_line;
    QLineF focal_line;
};

#endif // CONCAVE_LENS_H
