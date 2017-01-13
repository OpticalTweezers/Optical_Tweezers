#ifndef BIPRISM_H
#define BIPRISM_H
#include <QGraphicsPixmapItem>
#include <Light.h>
#include <QPointF>

class Biprism : public QGraphicsPixmapItem{
public:
    Biprism(QPointF center, double length, double width, double angle);
    QPointF intersect(Light light);
    void refract_in_BA(Light light);
    void refract_in_AC(Light light);
    void refract_in_BC(Light light);
    void refract_out_BA(Light light);
    void refract_out_AC(Light light);
    void refract_out_BC(Light light);
    void refract_out_C(Light light);
private:
    double angle;
    double length;
    double width;
    QPointF center;
    QPointF pA;
    QPointF pB;
    QPointF pC;
    QLineF lineBA;  //设直线的时候保证玻璃在右侧
    QLineF lineAC;
    QLineF lineCB;
private slots:
    void rotate(double rotate_angle);
};
#endif // BIPRISM_H
