#ifndef HERBIVORES_H
#define HERBIVORES_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class Herbivores : public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Herbivores(QObject *parent = 0);
    ~Herbivores();
    bool processCollidings(QList<QGraphicsItem *> collidins);
    int GetUid();

    static int newUID;
    const int uid;
    double hunger;//голод
    double stamina;//выносливость
    int hp;
    QPoint lastFood;
    QTimer *HerbivoresTimer;
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
    void moveForFood();
    void status();
};


#endif // HERBIVORES_H
