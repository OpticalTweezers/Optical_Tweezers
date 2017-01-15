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
    laserGenerator->set_range(-3600,3600);


    //background music
    QMediaPlayer * music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/music/game_bgm.mp3"));
    music->play();

    //add mirror
    mirror =new Mirror(QLineF(QPointF(500,400),QPointF(600,500)));
    scene->addItem(mirror);

    //add win_zone
    win_zone =new Win_Zone();
    scene->addItem(win_zone);

}

Ball *Game::get_ball(){
    return ball;
}

LaserGenerator* Game::get_lasergenerator(){
    qDebug()<<"1";
    return laserGenerator;
}

Mirror *Game::get_mirror(){
    return mirror;
}

Win_Zone *Game::get_win_zone(){
    return win_zone;
}

void Game::write_ball(Ball *bl){
    ball=bl;
}



