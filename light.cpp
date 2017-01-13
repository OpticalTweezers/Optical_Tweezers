#include "light.h"
#include "game.h"
#include <qmath.h>
#include <QDebug>
#include <QPen>
extern Game*game;
Light::Light(QPointF p, double angle){
    QLineF line_of_light;
    line_of_light.setP1(p);
    line_of_light.setAngle(angle);
    line_of_light.setLength(2500);
    this->setLine(line_of_light);
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    this->setPen(pen);
    this->reset_point_at_screen();
    this->intensity=1;
}
/*
Light::Light(QPointF p1,QPointF p2){
    this->line().setP1();
    this->line().setP2();
    this->line().setLength(2500);//不知道可不可以？
    this->reset_point_at_screen();;
    this->intensity=1;
}
*/

//求光线与固定线段的交点

QPointF Light::intersect_point(QLineF ln){
    double x0=this->line().p1().x();
    double y0=this->line().p1().y();
    double x1=ln.p1().x();
    double y1=ln.p1().y();
    double alpha= qDegreesToRadians(-this->line().angle());
    double beta= qDegreesToRadians(-ln.angle());
    //qDebug()<<x0<<y0<<x1<<y1;
    if(this->line().intersect(ln,nullptr)){          //nullptr
        //line与ln平行于y轴
        if(beta==90||beta==270){
            if(alpha==90||alpha==270)
                return QPointF(-1,-1);
            else{
                double x=x1;
                double y=qTan(alpha)*(x1-x0)+y0;
                return QPointF(x,y);
                //qDebug()<<x0<<y0<<x1<<y1<<alpha<<beta<<x<<y;
            }
        }
        else if(alpha==90||alpha==270){
            double x=x0;
            double y=y1+qTan(beta)*(x0-x1);
            return QPointF(x,y);
            //qDebug()<<x0<<y0<<x1<<y1<<alpha<<beta<<x<<y;
        }

        //line与ln平行
        else if(qTan(beta)==qTan(alpha)){
            return QPointF(-1,-1);
        }
        //普通情况
        else {
            double x = (y0-y1+x1*qTan(beta)-x0*qTan(alpha))/(qTan(beta)-qTan(alpha));
            double y = y0+qTan(alpha)*(x-x0);
            //qDebug()<<x0<<y0<<x1<<y1<<alpha<<beta<<x<<y;
            return QPointF(x,y);
        }
    }
}

//求出光线与屏幕的交点
QPointF Light::intersect_screen(){
    QLineF up(0,0,800,0);
    QLineF down(0,600,800,600);
    QLineF left(0,0,0,600);
    QLineF right(800,0,800,600);
    //qDebug()<<this->line().intersect(right,nullptr);
    //qDebug()<<intersect_point(right).y()<<"right_point";
    if(this->line().intersect(up,nullptr)==1) return intersect_point(up);
    else if(this->line().intersect(down,nullptr)==1) return intersect_point(down);
    else if(this->line().intersect(left,nullptr)==1) return intersect_point(left);
    else if(this->line().intersect(right,nullptr)==1) return intersect_point(right);
    //qDebug()<<intersect_point(right).x()<<"right_point";
}

//重置终点为与屏幕的交点
void Light::reset_point_at_screen(){
    //qDebug()<<"mark";
    //qDebug()<<intersect_screen().x();
    //qDebug()<<"mark2";
    this->line().setP2(intersect_screen());
}


//光线与平面镜的反射
void Light::reflect(QLineF l){
    Light light(QPointF(0,0),0);
    if(this->line().intersect(l,nullptr)!=1) return ;  //If the class definition declares a move constructor or move assignment operator,
                                                            //the implicitly declared copy constructor is defined as deleted
    else {
        QPointF p=intersect_point(l);
        this->line().setP2(p);
        double alpha = this->line().angle();
        double beta = l.angle();
        double ref_angle;
        ref_angle = (2*beta-alpha)>360 ? (2*beta-alpha)-360:(2*beta-alpha);
        game->lights.append(new Light(p,ref_angle));
        scene()->addItem(game->lights[game->lights.size()-1]);
    }
}

//设置光强
void Light::set_intensity(double i){
    this->intensity=i;
}

void Light::simple_refract_in(QLineF l){
     if(this->line().intersect(l,nullptr)==1){
        QPointF p0 = this->intersect_point(l);
        this->line().setP2(p0);
        double alpha = this->line().angle();
        double beta0 = l.angle();
        double beta;
        QLineF *tmp = new QLineF;
        tmp->setAngle(alpha-beta0);

        //只有光线从有向线段的左侧入射才向下执行
        if((tmp->angle()>180 && tmp->angle()<360)){
            beta = beta0 - 90;
        }
        else return;

        double i = beta - alpha;
        double sinr = qSin(i)/n;
        double r = qAsin(sinr);

        double gamma = beta + r;
        Light *refract_in = new Light(p0,gamma);
    }
}

void Light::simple_refract_out(QLineF l){
    if(this->line().intersect(l,nullptr)==1){
        QPointF p0 = this->intersect_point(l);
        this->line().setP2(p0);
        double alpha = this->line().angle();
        double beta0 = l.angle();
        double beta;
        QLineF *tmp = new QLineF;
        tmp->setAngle(alpha-beta0);

        //只有光线从有向线段的右侧入射才向下执行
        if((tmp->angle()<180 && tmp->angle()>0)){
            beta = beta0 + 90;
        }
        else return;

        double i = beta - alpha;
        double sinr = qSin(i)*n;

        //全反射判断
        if(sinr>=1) return;
        else{
            double r = qAsin(sinr);
            double gamma = beta - r;
            Light *refract_out = new Light(p0,gamma);
        }
    }
}

double Light::refract_angle(QLineF l){
    //以下代码与上个函数基本相同，只不过要返回出射角，以便双棱镜处使用
    if(this->line().intersect(l,nullptr)==1){
        QPointF p0 = this->intersect_point(l);
        this->line().setP2(p0);
        double alpha = this->line().angle();
        double beta0 = l.angle();
        double beta;
        QLineF *tmp = new QLineF;
        tmp->setAngle(alpha-beta0);

        //只有光线从有向线段的右侧入射才向下执行
        if((tmp->angle()<180 && tmp->angle()>0)){
            beta = beta0 + 90;
        }
        else return 9;

        double i = beta - alpha;
        double sinr = qSin(i)*n;

        //全反射判断
        if(sinr>=1) return 9;
        else{
            return qAsin(sinr);
        }
    }
    else return 9;
}

double Light::refract_angle_light(QLineF l){
        double non_degree=999
    //以下代码与上上个函数基本相同，只不过要返回出射光线的角度，以便双棱镜处使用
    if(this->line().intersect(l,nullptr)==1){
        QPointF p0 = this->intersect_point(l);
        this->line().setP2(p0);
        double alpha = this->line().angle();
        double beta0 = l.angle();
        double beta;
        QLineF *tmp = new QLineF;
        tmp->setAngle(alpha-beta0);

        //只有光线从有向线段的右侧入射才向下执行
        if((tmp->angle()<180 && tmp->angle()>0)){
            beta = beta0 + 90;
        }
        else return non_degree;

        double i = beta - alpha;
        double sinr = qSin(i)*n;

        //全反射判断
        if(sinr>=1) return non_degree;
        else{
            double r = qAsin(sinr);
            return (beta - r);
        }
    }
    else return non_degree;
}

