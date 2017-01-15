#ifndef BALL_H
#define BALL_H
#include <QGraphicsEllipseItem>
#include <QPixmap>
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QVector2D>
#include "Light.h"
#include "Fail_dialog.h"
class Ball:public QObject,public QGraphicsPixmapItem{    //bad inherited error
    Q_OBJECT
public:
    Ball(QGraphicsItem * parent=0);
    QPointF *intersect_point(Light *light);
    void refract(Light *light);       //折射核心函数
    bool intersect_with_light();

    Light * get_refract_in_ball();    //读取light
    Light * get_refract_out();        //
    void write_refract_in_ball(Light *light);  //写入light
    void write_refract_out(Light *light);      //
    QVector<QVector2D> get_forces();
    void add_forces(QVector2D force);
public slots:
    void move();                 //ball移动
    void v_change();         //与move配套
    void realize_refract();
    void force_add();
private:
    bool out_of_scene();   //move辅助函数
    QVector2D velocity;
    QVector2D acceleration;
    QVector2D force=QVector2D(0,0);
    const double radius = 35.5;
    const double n = 1.5;
    const double force_constant = 1;
    QPointF center;
    Fail_dialog *fail_dialog;
    //小球运动受力
    QVector<QVector2D>forces;

    Light *refract_in_ball=nullptr;
    Light *refract_out=nullptr;
//protected:
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BALL_H
