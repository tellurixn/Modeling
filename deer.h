#ifndef DEER_H
#define DEER_H

#include "herbivores.h"

class Deer : public Herbivores
{
    Q_OBJECT
public:
    Deer();
    ~Deer();
    QPainterPath shape() const override;
protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;
};

#endif // DEER_H
