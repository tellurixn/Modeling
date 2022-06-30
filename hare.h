#ifndef HARE_H
#define HARE_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>
#include <QPainter>
#include <QObject>

class Hare : public QObject, public QGraphicsItem{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    explicit Hare(QObject *parent = 0);
    ~Hare();
    bool processCollidings(QList<QGraphicsItem *> collidins);
    int GetUid();



protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;
private:
    static int newUID;
    const int uid;
    int hunger;//голод
    int stamina;//выносливость
    int age;//возраст
    int hp;
    char *gender;//пол
    QPoint lastFood;
    QPainterPath shape() const override;
    QTimer *hareTimer;

public slots:
    void move();
    void rest();
    void get_damage();
    void eat();
    void moveForFood();
    void status();

};


#endif // HARE_H
