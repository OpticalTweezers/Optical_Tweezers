#include <Ball.h>
#include <game.h>
#include <cstdio>
#include <QPainter>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QtMath>

extern Game *game;
Ball::Ball(QGraphicsItem *parent):QObject(),QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/Ball.png"));
    setPos(400,300);

    //initialazation of moving

    velocity.setX(0);
    velocity.setY(0);

    acceleration.setX(0);
    acceleration.setY(0);
    forces.append(QVector2D(0,0));

    QTimer *timer =new QTimer();

    connect(timer,SIGNAL(timeout()),this,SLOT(v_change()));
    timer->start(100);


    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100);

    connect(timer,SIGNAL(timeout()),this,SLOT(realize_refract()));
    timer->start(100);

    connect(timer,SIGNAL(timeout()),this,SLOT(force_add()));
    timer->start(100);

    /*
    qDebug()<<"mark1";
    qDebug()<<game;
    qDebug()<<"lasergenerator";
    if(game->get_lasergenerator()->get_lg_light()){
        qDebug()<<game;
        intersect_point(game->get_lasergenerator()->get_lg_light());

    }
    */
    qDebug()<<"later";
}

//球折射光线
QPointF *Ball::intersect_point(Light *light){
    QPointF * points =new QPointF [2];
    //x0 y0中心点
    //x1 y1 x2 y2线段两端
    double x0 = this->x()+radius;
    double y0 = this->y()+radius;
    double x1 = light->line().p1().x();
    double x2 = light->line().p2().x();
    double y1 = light->line().p1().y();
    double y2 = light->line().p2().y();
    //qDebug()<<x0<<y0<<x1<<x2<<y1<<y2<<"laser_angle"<<light->line().angle();
    //qDebug()<<light;
    if(x1==x2){
        if(radius*radius > (x1-x0)*(x1-x0)){
            return nullptr;
        }
        else{
            double y3=y0+sqrt(radius*radius-(x1-x0)*(x1-x0));
            double y4=y0-sqrt(radius*radius-(x1-x0)*(x1-x0));
            if((y3-y1)<(y4-y1)){
                points[0]=QPointF(x1,y3);
                points[1]=QPointF(x1,y4);
            }
            else{
                points[0]=QPointF(x1,y4);
                points[1]=QPointF(x1,y3);
            }
            return points;
        }
    }
    //(x1!=x2)
    else{
        double k = (y1-y2)/(x1-x2);

        double A = (k*k+1);
        double B = 2*(-x0-k*k*x1+k*y1-k*y0);
        double C = y1*y1+y0*y0+x0*x0+k*k*x1*x1
                -2*k*y1*x1+2*k*y0*x1-2*y1*y0-radius*radius;
        double delta = B*B-4*A*C;



        if(delta<=0) return nullptr;


        else{
            double x3 = (-B+sqrt(delta))/(2*A);
            double x4 = (-B-sqrt(delta))/(2*A);
            double xi;
            if((x3-x1)>(x4-x1)){
                double y3 = y1+k*(x3-x1);
                double y4 = y1+k*(x4-x1);
                points[1] =QPointF(x3,y3);
                points[0] =QPointF(x4,y4);
                //qDebug()<<"points";
                //qDebug()<<points[0];
                //qDebug()<<points[1];
            }
            else {
                double y4 = y1+k*(x4-x1);
                double y3 = y1+k*(x3-x1);
                points[1] =QPointF(x4,y4);
                points[0] =QPointF(x3,y3);
            }
            return points;
            //double yi = y1+k*(xi-x1);
            //QPointF intersect_point;
            //intersect_point.setX(xi);
            //intersect_point.setY(yi);
            //qDebug()<<x3;
            //qDebug()<<x4;
            //return intersect_point;
            }

        }
    }


void Ball::refract(Light *light){
    //qDebug()<<intersect_point(game->get_lasergenerator()->get_lg_light());
    if(!(refract_in_ball &&refract_out)){
        qDebug()<<"*";
        QPointF p_in;
        p_in.setX(intersect_point(light)[0].x());
        p_in.setY(intersect_point(light)[0].y());
        QLineF normal1;    //法线
        qDebug()<<p_in;
        qDebug()<<"**";
        normal1.setP1(center);
        normal1.setP2(p_in);
        double alpha1 = normal1.angle();
        double beta1 = light->line().angle();
        double i1 =(beta1-180-alpha1);
        //qDebug()<<alpha1;
        //qDebug()<<beta1;
        //qDebug()<<i1;
        double sinr1 = qSin(qDegreesToRadians(i1))/n;
        double r1 = qRadiansToDegrees(qAsin(sinr1));   //arcsin函数
        double gamma1 = alpha1+180+r1;
        //重置light端点
        QLineF lg_light(light->line().p1(),p_in);
        light->setLine(lg_light);

        refract_in_ball=new Light(p_in, gamma1);
        QPointF p_out = intersect_point(refract_in_ball)[1];

        //重置light in端点
        QLineF light_in(p_in,p_out);
        qDebug()<<p_in;
        qDebug()<<p_out;
        refract_in_ball->setLine(light_in);

        qDebug()<<"***";
        QLineF normal2;
        normal2.setP1(this->center);
        normal2.setP2(p_out);
        double alpha2 = normal2.angle();
        double beta2 = refract_in_ball->line().angle();

        qDebug()<<"****";
        double i2 = -(alpha2-beta2);
        double sinr2 = qSin(qDegreesToRadians(i2))*n;

        //全反射讨论
        if(sinr2>=1){
            qDebug()<<"*****";
            return;
        }
        else{
            qDebug()<<"******";
            double r2 =qRadiansToDegrees(qAsin(sinr2));
            double gamma2 = alpha2+r2;
            refract_out = new Light(p_out,gamma2);
            scene()->addItem(refract_in_ball);
            scene()->addItem(refract_out);
            qDebug()<<"$";

        }
      }



}

bool Ball::intersect_with_light(){
    Light* l=game->get_lasergenerator()->get_lg_light();
    if(l){
        if(!intersect_point(l)){
            //qDebug()<<"no_light";
            return false;
        }
        else return true;
    }
    else return false;
}

Light *Ball::get_refract_in_ball(){
    return refract_in_ball;
}

Light *Ball::get_refract_out(){
    return refract_out;
}

void Ball::write_refract_in_ball(Light *light){
    refract_in_ball=light;
}

void Ball::write_refract_out(Light *light){
    refract_out=light;
}

QVector<QVector2D> Ball::get_forces(){
    return forces;
}

void Ball::add_forces(QVector2D force_from_light){
    qDebug()<<force_from_light;
    forces.append(force_from_light);
    //qDebug()<<forces[0]<<forces[1];
}

//判断出屏幕
bool Ball::out_of_scene(){
    if(x()+pixmap().width()<0 ||x()>scene()->width()
        ||y()-pixmap().height()<0  ||y()>scene()->height())
        return true;
    else
        return false;
}
//ball运动
void Ball::move(){
    if(out_of_scene()){
        scene()->removeItem(this);
        delete this;
        fail_dialog =new Fail_dialog();
        fail_dialog->show();
        qDebug()<<"gameover";
        return;
    }
    center.setX(this->pos().x()+radius);
    center.setY(this->pos().y()+radius);

    double dx=velocity.x();
    double dy=velocity.y();
    setPos(x()+dx,y()+dy);


}

//ball受力改变velocity
void Ball::v_change(){
    double forceX;
    double forceY;
    for(int i=0;i<forces.size();i++){
        forceX+=forces[i].x();
    }
    for(int i=0;i<forces.size();i++){
        forceY+=forces[i].y();
    }
    force.setX(forceX);
    force.setY(forceY);

    velocity.setX(velocity.x()+force.x());
    velocity.setY(velocity.y()+force.y());
    qDebug()<<"force";
    qDebug()<<force.x();
    qDebug()<<force.y();
}

void Ball::realize_refract(){
    //qDebug()<<"SSS";
    //qDebug()<<intersect_with_light();
    bool flag=intersect_with_light();
    qDebug()<<"SS";
    if(game->get_lasergenerator()->get_lg_light()){
        if(refract_in_ball&&refract_out){
            if(flag){
                scene()->removeItem(refract_in_ball);
                scene()->removeItem(refract_out);
                write_refract_in_ball(nullptr);
                write_refract_out(nullptr);
                Light * tl=game->get_lasergenerator()->get_lg_light();
                //qDebug()<<'*'<<tl;
                refract(tl);
                //qDebug()<<"hello";
            }
            else{
                scene()->removeItem(refract_in_ball);
                scene()->removeItem(refract_out);
                write_refract_in_ball(nullptr);
                write_refract_out(nullptr);
                game->get_lasergenerator()->get_lg_light()->reset_point_at_screen(); //重置light_lg端点
            }
        }
        else{
            if(flag){
                Light * tl=game->get_lasergenerator()->get_lg_light();
                //qDebug()<<'*'<<tl;
                refract(tl);
            }
         }
    }

}

void Ball::force_add(){
    //qDebug()<<"add force?";
    //qDebug()<<game;
    Light * lt=(game->get_lasergenerator()->get_lg_light());
    //qDebug()<<lt;
    if(lt){                                 //考虑先后执行顺序，判断是否为空指针
        if(intersect_with_light()){
            double force_angle = (lt->line().angle()
                          +refract_out->line().angle())/2-270;
            qDebug()<<"add force? *";
            QVector2D force_from_light(qCos(qDegreesToRadians(force_angle)),-qSin(qDegreesToRadians(force_angle)));
            double force_scale =0.005;
            game->get_ball()->add_forces(force_scale*force_from_light);
            qDebug()<<force_angle;
            qDebug()<<force_from_light;
            exit(0);

        }
    }
}


/*     Non_use
void Ball::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget){
    QPainterPath path;
    path.addEllipse(pixmap().width()/2,pixmap().height()/2,30,30);
    painter->setClipPath(path);
    painter->drawPixmap(QPointF(pixmap().width()/2,pixmap().height()/2),my_pixmap);
    qDebug() <<"2333333";
}
    用painter来截取path的废代码
*/
