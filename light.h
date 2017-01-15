#ifndef LIGHT_H
#define LIGHT_H

#include <QPointF>
#include <QGraphicsLineItem>

class Light : public QGraphicsLineItem{
public:
    Light(QPointF,double angle);
    Light(Light& lt);
    //Light(QPointF p1, QPointF p2);
    QPointF *intersect_point(QLineF line);
    QPointF *intersect_screen();
    void reset_point_at_screen();
    void reflect(QLineF l);
    void set_intensity(double i);
    void simple_refract_in(QLineF l);
    void simple_refract_out(QLineF l);
    double refract_angle(QLineF l);
    double refract_angle_light(QLineF l);
    double get_d();
    double get_intensity();
    void write_d(double new_d);
    void write_intensity(double new_intensity);

    const double n = 1.5;
private:
    double intensity;
    double d = 0; //预设的光线宽度，双棱镜函数中使用
};

#endif // LIGHT_H
