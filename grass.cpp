#include "grass.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>

Grass::Grass() : QObject(), QGraphicsItem(){
    //int random;
    amount=0;
    x1 = 0;
    y1 = 0;
    x2 = 50;
    y2 = 50;
}

void Grass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawEllipse(x1,y1,x2,y2);
}

QRectF Grass::boundingRect() const
{
    return QRectF(0,0,50,50);
}
