#ifndef BALL_H
#define BALL_H
#include <QGraphicsEllipseItem>
#include <QPixmap>
#include <QPainterPath>
#include <QPainter>
#include <QGraphicsPixmapItem>
#include <QPointF>
#include <QVector2D>
class Ball:public QObject,public QGraphicsPixmapItem{    //bad inherited error
    Q_OBJECT
public:
    Ball(QGraphicsItem * parent=0);
public slots:
    void move();                 //ball移动
    void v_change(QVector2D force);         //与move配套
private:
    bool out_of_scene();   //move辅助函数
    QVector2D velocity;
    QVector2D acceleration;
//protected:
    //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // BALL_H
