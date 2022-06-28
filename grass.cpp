#include "grass.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>

Grass::Grass() :  QGraphicsItem(){

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
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(55,143,46));
    painter->drawEllipse(0,0,50,30);


}

QRectF Grass::boundingRect() const
{
    return QRectF(0,0,50,30);
}

QPainterPath Grass::shape() const
{
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
