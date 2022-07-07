#include "deer.h"
#include "mainwindow.h"
#include "qgraphicsscene.h"
#include "wolf.h"

Deer::Deer()
{

}

Deer::~Deer()
{

}

void Deer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    /*Отрисовка оленя*/
    painter->setPen(Qt::NoPen);

    painter->setBrush(QColor(186,135,89));

    painter->drawEllipse(0,0,15,15);


    /* Отрисовываем полоску жизни
       соизмеримо текущему здоровью
       относительно максимального здоровья
    */
      painter->setBrush(Qt::red);
      painter->drawRect(-2,-6, (int) 20*hp/100,3);
}

QRectF Deer::boundingRect() const
{
    return QRectF(-2,-6,20,20);
}

/*Возращение формы - эллипса*/
QPainterPath Deer::shape() const
{

    QPainterPath path;
    path.addEllipse(0,0,15,15);
    return path;
}


