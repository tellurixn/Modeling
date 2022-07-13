#ifndef WOLF_H
#define WOLF_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class Wolf : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Wolf(QObject *parent = 0);
    ~Wolf();
    bool processCollidings(QList<QGraphicsItem *> collidins);
    QPainterPath shape() const override;
public slots:
    void move();
    void rest();
    void get_damage();
    void eat(QList<QGraphicsItem *> colliding);
    void status();
private:
    double hunger;//голод
    double stamina;//выносливость
    int hp;//очки здоровья
    QTimer *WolfTimer;//таймер
    QPoint newPosition;//новая позиция на сцене
protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;

signals:
    void deerEaten();//олень съеден
    void hareEaten();//заяц съеден
    void wolfDead();//волк мертв
};

#endif // WOLF_H
