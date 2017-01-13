#ifndef LASERGENERATOR_H
#define LASERGENERATOR_H
#include <QGraphicsPixmapItem>

#include <QMouseEvent>

class LaserGenerator : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    LaserGenerator();
    void set_range(double left,double right);
private:
    double laser_angle;
    double left_range;
    double right_range;
public slots:
    void keyPressEvent(QKeyEvent *event);
};

#endif // LASERGENERATOR_H
