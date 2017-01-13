#include <Ball.h>
#include <game.h>
#include <QPainter>
#include <QPainter>
#include <QDebug>
#include <QTimer>
#include <QtMath>

extern Game *game;
Ball::Ball(QGraphicsItem *parent):QObject(),QGraphicsPixmapItem(parent){
    setPixmap(QPixmap(":/images/Ball.png"));
    setPos(400,300);
  
    this->center.setX(this->pos().x()+radius);
    this->center.setY(this->pos().y()+radius);

    //initialazation
    velocity.setX(10);
    velocity.setY(10);
    acceleration.setX(0);
    acceleration.setY(0);

    QVector2D F(0,10);

    QTimer *timer_a =new QTimer();

    connect(timer_a,SIGNAL(timeout()),this,SLOT(v_change(F)));
    timer_a->start(100);

    QTimer *timer_v =new QTimer();
    connect(timer_v,SIGNAL(timeout()),this,SLOT(move()));
    timer_v->start(100);
}

//球折射光线
QPointF Ball::intersect_point(Light light){

    //不合理值的返回
    QPointF non_point(-1,-1);
    
    double x0 = this->x()+radius;
    double y0 = this->y()+radius;
    double x1 = light.line().p1().x();
    double x2 = light.line().p2().x();
    double y1 = light.line().p1().y();
    double y2 = light.line().p2().y();

    if(x1=x2){
        if(radius*radius > (x1-x0)*(x1-x0)){
            return QPointF(-2,1);
        }
        else{
            double y3=y0+sqrt(radius*radius-(x1-x0)*(x1-x0));
            double y4=y0-sqrt(radius*radius-(x1-x0)*(x1-x0));
            double yi=(y1-y3)>(y1-y4)? y4:y3;
            return QPointF(x1,yi);
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



        if(delta<=0) return non_point;


        else{
            double x3 = (-B+sqrt(delta))/(2*A);
            double x4 = (-B+sqrt(delta))/(2*A);
            double xi;
            if((x3-x1)>(x4-x1)){
                xi=x4;
            }
            else{
                xi=x3;
                double yi = y1+k*(xi-x1);
                QPointF intersect_point;
                intersect_point.setX(xi);
                intersect_point.setY(yi);
                return intersect_point;
            }
        }
    }
}

void Ball::refract(Light light){
    QPointF p_in;
    p_in.setX(intersect_point(light).x());
    p_in.setY(intersect_point(light).y());
    QLineF normal1;
  
    normal1.setP1(center);
    normal1.setP2(p_in);
    double alpha1 = normal1.angle();
    double beta1 = light.line().angle();
    double i1 = 180-(beta1-alpha1);
    double sinr1 = qSin(i1)/n;
    double r1 = qAsin(sinr1);   //arcsin函数
    double gamma1 = alpha1-180+r1;
    light.line().setP2(p_in);
    Light *refract_in_ball = new Light(p_in, gamma1);
    QPointF p_out = intersect_point(refract_in_ball);

    QLineF normal2;
    normal2.setP1(this->center);
    normal2.setP2(p_out);
    double alpha2 = normal2.angle();
    double beta2 = refract_in_ball->line().angle();
  
    double i2 = 180-(beta2-alpha2);
    double sinr2 = qSin(i2)*n;

    //全反射讨论
    if(sinr2>=1){
        return;
    }
    else{
        double r2 = qAsin(sinr2);
        double gamma2 = alpha2-180+r2;
        refract_in_ball->line().setP2(p_out);
        Light *refract_out = new Light(p_out,gamma2);

        scene()->addItem(refract_in_ball);
        scene()->addItem(refract_out);
        double force_angle = (light.line().angle()
                              -refract_out->line().angle())/2+180;
        double force = force_angle * force_constant;
    }
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
    double dx=velocity.x();
    double dy=velocity.y();
    setPos(x()+dx,y()+dy);
}

//ball受力改变velocity
void Ball::v_change(QVector2D force){
    velocity.setX(velocity.x()+force.x());
    velocity.setY(velocity.y()+force.y());
    qDebug()<<velocity.x();
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
