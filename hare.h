#ifndef HARE_H
#define HARE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class Hare : public QObject,public QGraphicsItem{
    Q_OBJECT
public:
    Hare();

 protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;
private:
    int hunger;
    int stamina;
    int age;
    char gender;
};


#endif // HARE_H
