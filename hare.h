#ifndef HARE_H
#define HARE_H

#include "herbivores.h"

class Hare : public Herbivores
{
public:
    Hare();
    ~Hare();
    QPainterPath shape() const override;
protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;
    /*Возращение эллипса, в котором находится элемент*/

};

#endif // HARE_H
