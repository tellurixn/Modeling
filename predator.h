#ifndef PREDATOR_H
#define PREDATOR_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class Predator : public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Predator(QObject *parent = 0);
    ~Predator();
    bool processCollidings(QList<QGraphicsItem *> collidins);

    double hunger;//голод
    double stamina;//выносливость
    int hp;

    QTimer *predatorTimer;

    int GetUid();

    static int newUID;
    const int uid;

protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;

public slots:
    void move();
    void rest();
    void get_damage();
    void eat();
    void status();
};

#endif // PREDATOR_H
