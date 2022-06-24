#include "hare.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>

Hare::Hare() : QObject(), QGraphicsItem(){
    srand(time(NULL));

    char gndr[2]={'m','f'};
    int random = rand()%2;
    gender = gndr[random];

    hunger = 100;
    stamina = 100;
    age = 0;

}

void Hare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);

    if(gender == 'm'){
        painter->setBrush(QColor(128,128,128));
    }
    else{
        painter->setBrush(QColor(Qt::white));
    }

    painter->drawEllipse(0,0,10,10);



}

QRectF Hare::boundingRect() const
{
    return QRectF(0,0,50,50);
}
