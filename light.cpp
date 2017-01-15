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
    //qDebug()<<line_of_light.angle();
    //qDebug()<<this->line().angle();
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    this->setPen(pen);
    this->reset_point_at_screen();
    this->intensity=1;
    //qDebug()<<this->line().p2();
    //exit(0);
}

Light::Light(Light &lt){
    QPen pen;
    pen.setColor(Qt::white);
    pen.setWidth(2);
    this->setPen(pen);
    this->intensity=1;
    this->setLine(lt.line());
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

QPointF *Light::intersect_point(QLineF ln){
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
                return nullptr;
            else{
                double x=x1;
                double y=qTan(alpha)*(x1-x0)+y0;
                QPointF* the_intersec_point =new QPointF(x,y);
                return the_intersec_point;
                //qDebug()<<x0<<y0<<x1<<y1<<alpha<<beta<<x<<y;
            }
        }
        else if(alpha==90||alpha==270){
            double x=x0;
            double y=y1+qTan(beta)*(x0-x1);
            QPointF* the_intersec_point =new QPointF(x,y);
            return the_intersec_point;
            //qDebug()<<x0<<y0<<x1<<y1<<alpha<<beta<<x<<y;
        }

        //line与ln平行
        else if(qTan(beta)==qTan(alpha)){
            return nullptr;
        }
        //普通情况
        else {
            double x = (y0-y1+x1*qTan(beta)-x0*qTan(alpha))/(qTan(beta)-qTan(alpha));
            double y = y0+qTan(alpha)*(x-x0);
            //qDebug()<<x0<<y0<<x1<<y1<<alpha<<beta<<x<<y;
            QPointF* the_intersec_point =new QPointF(x,y);
            return the_intersec_point;
        }
    }
}

//求出光线与屏幕的交点
QPointF *Light::intersect_screen(){
    QLineF up(0,0,800,0);
    QLineF down(0,600,800,600);
    QLineF left(0,0,0,600);
    QLineF right(800,0,800,600);

    //重置光线P2
    QLineF new_reset_line(this->line());
    new_reset_line.setLength(2500);
    this->setLine(new_reset_line);
    //qDebug()<<this->line().intersect(right,nullptr);
    //qDebug()<<*intersect_point(right).y()<<"right_point";
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
    QLineF new_Line(this->line().p1(),*intersect_screen());
    this->setLine(new_Line);
    //qDebug()<<intersect_screen();
    //qDebug()<<this->line().p2();
}



void Light::set_intensity(double i){
    this->intensity=i;
}

void Light::simple_refract_in(QLineF l){
     if(this->line().intersect(l,nullptr)==1){
        QPointF p0 = *intersect_point(l);
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
        QPointF p0 = *intersect_point(l);
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
        QPointF p0 = *intersect_point(l);
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
        double non_degree=999;
    //以下代码与上上个函数基本相同，只不过要返回出射光线的角度，以便双棱镜处使用
        if(this->line().intersect(l,nullptr)==1){
            QPointF p0 = *intersect_point(l);
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


double Light::get_d(){
    return d;
}

double Light::get_intensity(){
    return intensity;
}

void Light::write_d(double new_d){
    d=new_d;
}

void Light::write_intensity(double new_intensity){
    intensity=new_intensity;
}

