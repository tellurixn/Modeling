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
    /*Конструктор*/
    explicit Herbivores(QObject *parent = 0);
    /*Деструктор*/
    ~Herbivores();
    /*Функция обнаруживающая столкновение с другими объектами*/
    bool processCollidings(QList<QGraphicsItem *> collidins);

    double hunger;//голод
    double stamina;//выносливость
    int hp;//очки здоровья
    QPoint lastFood;//координаты последнего приема пищи
    QTimer *HerbivoresTimer;//таймер объекта
    QPoint newPosition;//новая позиция на сцене
public slots:
    void move(); //функция движения
    void rest(); //функция отдыха
    void get_damage(); // функция получения урона
    void eat(); //функция приема пищи
    void moveForFood();// функция движения к последней пище
    void status(); //функция опроса состояния объекта
protected:
    /*Отрисовка элемента*/
    void paint(QPainter *painter,const QStyleOptionGraphicsItem *option,QWidget *widget = nullptr) override;
    /*Возращение прямоугольника, в котором находится элемент*/
    QRectF boundingRect() const override;


};


#endif // HERBIVORES_H
