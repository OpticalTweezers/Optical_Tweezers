#ifndef LASERGENERATOR_H
#define LASERGENERATOR_H
#include <QGraphicsPixmapItem>

#include <QMouseEvent>

#include <QMediaPlayer>

class LaserGenerator : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    LaserGenerator();
private:
    double laser_angle;
    QMediaPlayer * lasersound;
public slots:
    void keyPressEvent(QKeyEvent *event);

};

#endif // LASERGENERATOR_H
