#ifndef GRASS_H
#define GRASS_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class Grass : public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    Grass();

 protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;
private:
    int amount;
};

#endif // GRASS_H
