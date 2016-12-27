#ifndef LIGHT_H
#define LIGHT_H

#include <QPointF>
#include <QGraphicsLineItem>

class Light:public QGraphicsLineItem{
public:
    Light(QPointF,double angle);
    Light(QLineF);
    QPointF intersect_point(QLineF line);
    QPointF intersect_screen();
    void reset_point_at_screen();
};

#endif // LIGHT_H
