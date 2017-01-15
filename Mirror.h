#ifndef MIRROR_H
#define MIRROR_H

#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QLineF>
#include <QVector>
#include <QObject>
#include "Light.h"

class Mirror :public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Mirror(QLineF l);
    QVector <Light*>mirror_reflected_light;
    void reflect(Light *lt);
private:
    QPointF mid_point;
    QLineF mid_line;

public slots:
    void rotate(double rotate_angle);
    void reflect_light();
};

#endif // MIRROR_H
