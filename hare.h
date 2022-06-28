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
    void look_for_food();
    bool processCollidings(QList<QGraphicsItem *> collidins);

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
    QPainterPath shape() const override;
    QTimer *hareTimer;
private slots:
    void debug();
    void move();
};


#endif // HARE_H
