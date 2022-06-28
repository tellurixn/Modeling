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
    bool processCollidings(QList<QGraphicsItem *> collidins);


protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;
private:
    int hunger;//голод
    int stamina;//выносливость
    int age;//возраст
    int hp;
    char gender;//пол


    QPainterPath shape() const override;
    QTimer *hareTimer;
public slots:
    void move();
    void rest();
    void get_damage();
    void eat();
    void status();


};


#endif // HARE_H
