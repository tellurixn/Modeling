#include "grass.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>

Grass::Grass() :  QGraphicsItem()
{

}

Grass::~Grass()
{

}

void Grass::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    /*Отрисовка объекта трава*/
    Q_UNUSED(option)
    Q_UNUSED(widget)
    painter->setPen(Qt::NoPen);
    painter->setBrush(QColor(55,143,46));
    painter->drawEllipse(0,0,50,30);


}

QRectF Grass::boundingRect() const
{
    /*Возврат прямоугольника-области объекта*/
    return QRectF(0,0,50,30);
}

QPainterPath Grass::shape() const
{
    /*Возврат эллипса-области объекта*/
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
