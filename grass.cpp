#include "grass.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>

Grass::Grass() : QObject(), QGraphicsItem(){
    srand(time(NULL));
    int random_x1 = -240 + rand() % 481;
    int random_y1 = -90 + rand() % 181;
    int random_x2 = -240 + rand() % 481;
    int random_y2 = -90 + rand() % 181;
    amount=0;
    x1 = random_x1;
    y1 = random_y1;
    x2 = random_x2;
    y2 = random_y2;
}

void Grass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(55,143,46));
    painter->drawEllipse(x1,y1,x2,y2);


}

QRectF Grass::boundingRect() const
{
    return QRectF(0,0,50,50);
}
