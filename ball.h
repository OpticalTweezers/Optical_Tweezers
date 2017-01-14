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
    QPointF intersect_point(Light *light);
    void refract(Light *light);
    bool intersect_with_light();
public slots:
    void move();                 //ball移动
    void v_change();         //与move配套
private:
    bool out_of_scene();   //move辅助函数
    QVector2D velocity;
    QVector2D acceleration;
    QVector2D force=QVector2D(0,2);
    const double radius = 35.5;
    const double n = 1.5;
    const double force_constant = 1;
    QPointF center;
    Fail_dialog *fail_dialog;
    //小球运动受力
    QVector<QVector2D>forces;

    //不合理值定义
    QPointF non_point=QPointF(-1,-1);
//protected:
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BALL_H
