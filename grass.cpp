#include "grass.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>

Grass::Grass() : QObject(), QGraphicsItem(){

    /*Если трава появилась впервые, кол-во = 1*/
    if(amount == NULL){
        amount = 1;
    }
    else{
        amount++;
    }
}

void Grass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(55,143,46));
    painter->drawEllipse(0,0,50,30);


}

QRectF Grass::boundingRect() const
{
    return QRectF(0,0,50,30);
}
