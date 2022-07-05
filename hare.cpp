#include "hare.h"


Hare::Hare()
{

}

Hare::~Hare()
{

}

void Hare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::NoPen);

    painter->setBrush(QColor(Qt::white));

    painter->drawEllipse(0,0,10,10);

    /* Отрисовываем полоску жизни
       соизмеримо текущему здоровью
       относительно максимального здоровья
    */
    painter->setBrush(Qt::red);
    painter->drawRect(-2,-5, (int) 14*hp/100,3);

}

QRectF Hare::boundingRect() const
{
    return QRectF(-2,-5,14,15);
}

/*Возращение формы - эллипса*/
QPainterPath Hare::shape() const
{
    /*Функция возращает форму в виде эллипса*/
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}
