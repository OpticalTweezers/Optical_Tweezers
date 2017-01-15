#include "Biprism.h"
#include <qmath.h>

Biprism::Biprism(QPointF center, double length, double width, double angle){
    //this->setPixmap(":/images/biprism");
    this->center = center;
    this->setTransformOriginPoint(center);
    this->pA = QPointF(center.x(),center.y()-length/2);
    this->pB = QPointF(center.x(),center.y()+length/2);
    this->pC = QPointF(center.x()+width,center.y());
    this->rotate(angle);
}

void Biprism::refract_in_BA(Light light){
    light.simple_refract_in(lineBA);
}

void Biprism::refract_in_AC(Light light){
    light.simple_refract_in(lineBA);
}

void Biprism::refract_in_CB(Light light){
    light.simple_refract_in(lineCB);
}

void Biprism::refract_out_BA(Light light){
    light.simple_refract_out(lineBA);
}

void Biprism::refract_out_AC(Light light){
    if(light.intersect_point(this->lineAC)) return;
    else if(light.refract_angle(this->lineAC)==9) return;
    else{
        QPointF p0 = *light.intersect_point(this->lineAC);
        QLineF tmp = QLineF(p0,pC);
        double x = tmp.length();
        double theta = light.refract_angle(this->lineAC);
        double critical = light.get_d()/qCos(theta);
        if(x>=critical){
            light.simple_refract_out(lineAC);
        }
        else {

            //假设一条C方向延长的CB边，以便求出射光线的角度
            QLineF tmpBC = QLineF(pB,pC);
            tmpBC.setLength(tmpBC.length()+100);
            QPointF pCtmp = tmpBC.p2();
            QLineF tmpCB = QLineF(pCtmp,pB);
            double thetaAC = light.refract_angle_light(lineAC);
            double thetaCB = light.refract_angle_light(tmpCB);
            Light *outAC = new Light(pC,thetaAC);
            Light *outCB = new Light(pC,thetaCB);

            //调整光强
            outAC->write_intensity(light.get_intensity()* (critical+x)*(critical+x)/
                    (critical-x)*(critical-x)+(critical+x)*(critical+x));
            outCB->write_intensity(light.get_intensity()* (critical-x)*(critical-x)/
                    (critical-x)*(critical-x)+(critical+x)*(critical+x));
        }
    }
}


void Biprism::refract_out_CB(Light light){
    if(light.intersect_point(this->lineAC)) return;
    else if(light.refract_angle(this->lineAC)==9) return;
    else{
        QPointF p0 = *light.intersect_point(this->lineAC);
        QLineF tmp = QLineF(p0,pC);
        double x = tmp.length();
        double theta = light.refract_angle(this->lineAC);
        double critical = light.get_d()/qCos(theta);
        if(x>=critical){
            light.simple_refract_out(lineAC);
        }
        else {

            //假设一条延长的AC边，以便求出射光线的角度
            QLineF tmpAC = QLineF(pA,pC);
            tmpAC.setLength(tmpAC.length()+100);
            double thetaAC = light.refract_angle_light(tmpAC);
            double thetaCB = light.refract_angle_light(lineCB);
            Light *outAC = new Light(pC,thetaAC);
            Light *outCB = new Light(pC,thetaCB);

            //调整光强
            outAC->write_intensity(light.get_intensity()* (critical+x)*(critical+x)/
                    (critical-x)*(critical-x)+(critical+x)*(critical+x));
            outCB->write_intensity(light.get_intensity()* (critical-x)*(critical-x)/
                    (critical-x)*(critical-x)+(critical+x)*(critical+x));
        }
    }
}

void Biprism::rotate(double rotate_angle){
    this->setTransformOriginPoint(center);
    this->rotate(rotate_angle);
    QLineF tmpA = QLineF(center,pA);
    QLineF tmpB = QLineF(center,pB);
    QLineF tmpC = QLineF(center,pC);
    tmpA.setAngle(tmpA.angle()+rotate_angle);
    tmpB.setAngle(tmpB.angle()+rotate_angle);
    tmpC.setAngle(tmpC.angle()+rotate_angle);
    pA = QPointF(tmpA.p2());
    pB = QPointF(tmpB.p2());
    pC = QPointF(tmpC.p2());
    this->lineBA = QLineF(pB,pA);
    this->lineAC = QLineF(pA,pC);
    this->lineCB = QLineF(pC,pB);
}


