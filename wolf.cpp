#include "wolf.h"
#include "hare.h"
#include "deer.h"
#include "qgraphicsscene.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <QApplication>
#include <QDateTime>
#include <QVector2D>

static int randomBetween(int low, int high, int seed)
{
    srand(seed);
    return (rand() % ((high + 1) - low) + low);
}

Wolf::Wolf(QObject *parent) : QObject(parent)
{
    hunger = 100;
    hp = 100;
    stamina = 100;
    WolfTimer = nullptr;

    /*Берем рандомную точку на сцене*/
    newPosition = QPoint(randomBetween(30,650,rand()),randomBetween(10,250,rand()));
    qDebug() << "Construcror's  newPos = (" << newPosition.x() << ", "<< newPosition.y() <<")";
}

Wolf::~Wolf()
{

}

/*Обнаружение столкновений*/
bool Wolf::processCollidings(QList<QGraphicsItem *> collidins)
{
    bool can_eat = false;
      for (QGraphicsItem* item: collidins) {
          if (dynamic_cast<Hare*> (item)){//если объект класса Hare
              can_eat = true;//можно есть
          }
          if (dynamic_cast<Deer*> (item)){//если объект класса Deer
              can_eat = true;//можно есть
          }
      }
      return can_eat;
}

void Wolf::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::NoPen);

    painter->setBrush(QColor(Qt::gray));

    painter->drawEllipse(0,0,17,17);

    /* Отрисовываем полоску жизни
       соизмеримо текущему здоровью
       относительно максимального здоровья
    */
    painter->setBrush(Qt::red);
    painter->drawRect(-2,-8, (int) 22*hp/100,3);
}

QRectF Wolf::boundingRect() const
{
    return QRectF(-2,-8,22,25);
}

QPainterPath Wolf::shape() const
{
    QPainterPath path;
    path.addEllipse(0,0,17,17);
    return path;
}

void Wolf::move()
{
    /*К выбранной рандомной точке прокладывается прямая
    движение происходит по уравнению прямой через 2 точки*/

    //если еще не сместился на другой конец прямой
    if(pos().x() != newPosition.x() && pos().y()!= newPosition.y()){

    if(newPosition.x() < pos().x()){ //если точка левее уменьшаем x на 1 каждый шаг
        int oldX = pos().x(),//старые
            oldY = pos().y();//координаты

        int newX = oldX - 1,//новый икс
           //новый игрек
           newY = ((newX - oldX)*(newPosition.y()-oldY))/(newPosition.x() - oldX) + oldY;

        setPos(newX,newY);
    }
    else{ //если точка правее прибавляем к иксу единицу каждый шаг
        int oldX = pos().x(),//старые
               oldY = pos().y();//координаты

        int newX = oldX + 1,//новый икс
               //новый игрек
               newY = ((newX - oldX)*(newPosition.y()-oldY))/(newPosition.x() - oldX) + oldY;

        setPos(newX,newY);
        }
    }
    else{
        //новая точка выбирается когда закончил передвижение по предыдущей прямой
        newPosition = QPoint(randomBetween(30,650,rand()),randomBetween(10,250,rand()));
    }

    stamina -=0.25;//за шаш выносливость -0,25
    hunger -= 0.25;//голод -0,25
    if (hunger<=0)
        hunger = 0;

}

void Wolf::rest()
{
    if (stamina<100){
        stamina += 1;
        hunger -= 0.25;
        if (hunger<=0)
            hunger = 0;
    }
    else{
        delete WolfTimer;//удаление таймера
        WolfTimer = nullptr;//присвоить nullptr
    }
}

void Wolf::get_damage()
{
    if(hp>=2)
        hp -= 2;
    else{
        hp = 0;
        emit wolfDead();
        this->deleteLater();

    }
}

void Wolf::eat(QList<QGraphicsItem *> colliding)
{
    for (QGraphicsItem* item: colliding) {
        if (dynamic_cast<Hare*> (item)){//Если наткнулся на зайца
            hunger+=20; //уменьшил голод
            if(hunger>100)
               hunger = 100;
            hp += 30;//восстановил здоровье
            if(hp>100)
               hp = 100;

            static_cast<Hare*> (item)->deleteLater(); //удалил зайца
            emit hareEaten();//вызвал сигнал заяц съеден
        }
        if (dynamic_cast<Deer*> (item)){ //если наткнулся на оленя
            hp -= 40;//получил урон от него
            if(hp<=0){//если очки здоровья после этого <=0
                emit wolfDead();//волк умер
                this->deleteLater();//удалил волка
                return;
            }
            hunger += 50;//если выжил то восстановил голод
            if(hunger>100)
                hunger = 100;
            hp += 45; //восстановил здоровьк
            if(hp>100)
               hp = 100;

            static_cast<Deer*> (item)->deleteLater();//удалил оленя
            emit deerEaten();//вызвал сигнал олень съеден
        }
    }
}

void Wolf::status()
{
    /*Случайное число от 50 до 85*/
    int random = randomBetween(50,85,rand());

    /*Список объектов с которыми столкнулся*/
    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    /*двигаться если стамина больше random и хищник не отдыхает*/
    if(stamina >=random && WolfTimer == nullptr){
        move();
    }

    /*отдых если стамина меньше random*/
    if(stamina < random){
        WolfTimer = new QTimer;
        connect(WolfTimer,SIGNAL(timeout()),this,SLOT(rest()));
        WolfTimer->start(250);
    }
    /*Если голод падает ниже 10 каждую секунду теряет 5 хп*/
    if(hunger <= 10){
        get_damage();
    }

    /*Если обнаружил зайца или оленя, то съел их*/
    if (processCollidings(colliding) == true) {
        eat(colliding);
    }

}
