#ifndef WIN_ZONE_H
#define WIN_ZONE_H

#include <QGraphicsPixmapItem>
#include <QPointF>

class Win_Zone : public QGraphicsPixmapItem {
public:
    Win_Zone(QPointF center, double width, double height);

};

#endif // WIN_ZONE_H
