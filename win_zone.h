#ifndef WIN_ZONE_H
#define WIN_ZONE_H

#include <QGraphicsPixmapItem>
#include <QPointF>
#include <Win_dialog.h>
#include <QTimer>
class Win_Zone :public QObject,public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Win_Zone();
public slots:
    void detect_ball();
private:
    Win_dialog *win_dialog;
    QTimer *timer;
};

#endif // WIN_ZONE_H
