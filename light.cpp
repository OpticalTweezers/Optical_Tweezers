#include "light.h"
#include "game.h"
#include <qmath.h>
extern Game*game;
Light::Light(QPointF p, double angle){
    this->line().setAngle(angle);
    this->line().setP1(p);
    this->line().setLength(2500);
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
    double y0=this->line().p2().y();
    double x1=ln.p1().x();
    double y1=ln.p2().y();
    double alpha=this->line().angle();
    double beta=ln.angle();
    if(this->line().intersect(ln,nullptr)){          //nullptr
        if(alpha==90 || alpha==270) ;
        else if(beta==90 || beta==270) ;
        else if(qTan(beta)!=qTan(alpha)){
            double x = y1-y0+x1*qTan(beta)-x0*qTan(alpha)/(qTan(beta)-qTan(alpha));
            double y = y0-qTan(alpha)*(x-x0);
            return QPointF(x,y);
        }
        else return nullptr;
    }
}

//求出光线与屏幕的交点
QPointF Light::intersect_screen(){
    QLineF up(0,0,scene()->width(),0);
    QLineF down(0,scene()->height(),scene()->width(),scene()->height());
    QLineF left(0,0,0,scene()->height());
    QLineF right(scene()->width(),0,scene()->width(),scene()->height());
    if(this->line().intersect(up,nullptr)==2) return intersect_point(up);
    else if(this->line().intersect(down,nullptr)==2) return intersect_point(down);
    else if(this->line().intersect(left,nullptr)==2) return intersect_point(left);
    else if(this->line().intersect(right,nullptr)==2) return intersect_point(right);
    else return QPointF(-200,-200);
}

//重置终点为与屏幕的交点
void Light::reset_point_at_screen(){
    this->line().setP2(intersect_screen());
}

//光线与平面镜的反射
void Light::reflect(QLineF l){
    Light light(QPointF(0,0),0);
    if(this->line().intersect(l,nullptr)!=1) return -1;  //If the class definition declares a move constructor or move assignment operator,
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
        else return 9;

        double i = beta - alpha;
        double sinr = qSin(i)*n;

        //全反射判断
        if(sinr>=1) return 9;
        else{
            double r = qAsin(sinr);
            return (beta - r);
        }
    }
    else return 9;
}

