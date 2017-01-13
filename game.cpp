#include <Game.h>
#include <light.h>
#include <QPen>
#include <QDebug>
#include <QMediaPlayer>
Game::Game(){
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

    //light
    Light *light=new Light(QPoint(700,700),45);
    //QGraphicsLineItem *lineitem=new QGraphicsLineItem(QLineF(QPoint(500,500),QPoint(600,600)));
    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(10);
    light->setPen(pen);
    scene->addItem(light);

    //background music
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/music/game_bgm.mp3"));
    music->play();
}



