#ifndef LASERGENERATOR_H
#define LASERGENERATOR_H
#include <QGraphicsPixmapItem>

#include <QMouseEvent>

class LaserGenerator : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    LaserGenerator();
private:
    double laser_angle;
public slots:
    void keyPressEvent(QKeyEvent *event);

};

#endif // LASERGENERATOR_H
