#ifndef LASERGENERATOR_H
#define LASERGENERATOR_H
#include <QGraphicsPixmapItem>
#include <QMouseEvent>
#include <QKeyEvent>
#include <light.h>
#include <QMediaPlayer>

class LaserGenerator : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    LaserGenerator();
    void set_range(double left,double right);

    //private接口
    Light *get_lg_light();
private:
    double laser_angle;
    double left_range;
    double right_range;
    QMediaPlayer * lasersound;
    Light *light=nullptr;
    bool mPressFlag_Space=false;
public slots:
    void keyPressEvent(QKeyEvent *event);
    //void keyReleaseEvent(QKeyEvent *event);
};

#endif // LASERGENERATOR_H
