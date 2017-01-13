#include <Game11.h>
#include <QDebug>

Game11::Game11(){
    //create a scene
    scene =new QGraphicsScene();
    setScene(scene);
    setFixedSize(800,600);
    scene->setSceneRect(0,0,800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    qDebug()<<scene->height();
    //add Ball
    ball=new Ball();
    scene->addItem(ball);
    //set background
    scene->setBackgroundBrush(QBrush(QPixmap(":/images/background.jpeg")));

    //add laserGenerator
    laserGenerator=new LaserGenerator();
    scene->addItem(laserGenerator);
    laserGenerator->setFlag(QGraphicsItem::ItemIsFocusable);
    laserGenerator->setFocus();  //继续debug

    //add mirror
    mirror =new Mirror(QLineF(QPointF(500,400),QPointF(600,500)));
    scene->addItem(mirror);
}
