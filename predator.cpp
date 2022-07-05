#include "predator.h"
#include "hare.h"
#include "deer.h"
#include "qgraphicsscene.h"
#include <QTimer>
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <QApplication>
#include <QDateTime>
#include <QVector2D>

int Predator::newUID = 0;

static int randomBetween(int low, int high, int seed)
{
    srand(seed);
    return (rand() % ((high + 1) - low) + low);
}

Predator::Predator(QObject *parent) : QObject(parent)  , uid(newUID++)
{

    hunger = 100;
    hp = 100;
    stamina = 100;
    predatorTimer = nullptr;

}

Predator::~Predator()
{

}

int Predator::GetUid()
{
    return uid;
}

bool Predator::processCollidings(QList<QGraphicsItem *> collidins)
{
    bool can_eat = false;
      for (QGraphicsItem* item: collidins) {
          if (dynamic_cast<Hare*> (item)){
              can_eat = true;
              hunger+=20;
              if(hunger>100)
                  hunger = 100;
              static_cast<Hare*> (item)->deleteLater();
              qDebug() << "Predator with ID = " << GetUid() << " eat hare";
          }
          if (dynamic_cast<Deer*> (item)){
              can_eat = true;
              hunger += 50;
              if(hunger>100)
                  hunger = 100;
              static_cast<Deer*> (item)->deleteLater();
              qDebug() << "Predator with ID = " << GetUid() << " eat deer";
          }
      }
      return can_eat;
}

void Predator::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
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

QRectF Predator::boundingRect() const
{
    return QRectF(-2,-8,22,25);
}

void Predator::move()
{
    /*Рандомные новые координаты*/
    QPointF newPos = QPointF(pos().x() + randomBetween(-15,15,rand()),
                             pos().y() + randomBetween(-15,15,rand()));

    /*Ограничение по координатам
    для предотвращения выхода за границы*/
    if(pos().x()>=650 || pos().y()>=280){
        newPos.setX(pos().x() - 15);
        newPos.setY(pos().y() - 15);

    }
    else if(pos().x()<=30 || pos().y()<=10){
        newPos.setX(pos().x() + 15);
        newPos.setY(pos().y() + 15);
    }

    //установка новой позиции
    setPos(newPos);
    stamina -=0.5;
    hunger -= 0.5;
    if (hunger<=0)
        hunger = 0;
}

void Predator::rest()
{
    if (stamina<100){
        qDebug() << "Predator with ID = " << GetUid() << " resting";
        stamina += 1;
        hunger -= 0.5;
        if (hunger<=0)
            hunger = 0;
    }
    else{
        delete predatorTimer;//удаление таймера
        predatorTimer = nullptr;//присвоить nullptr
    }
}

void Predator::get_damage()
{
    if(hp>=5)
        hp -= 5;
    else{
        hp = 0;
        this->deleteLater();
    }
}

void Predator::eat()
{
    qDebug() << "Someone eaten";
}

void Predator::status()
{
    qDebug() << "Predator ID = " << GetUid() << " status cheack";
   // int random = randomBetween(50,85,rand());
    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    /*двигаться если стамина больше 50 и хищник не отдыхает*/
    if(stamina >=50 && predatorTimer == nullptr){
        qDebug() << "Predator with ID = " << GetUid() << " is moving";
        move();

    }
    /*отдых если стамина меньше 50*/
    if(stamina < 50){
        predatorTimer = new QTimer;
        connect(predatorTimer,SIGNAL(timeout()),this,SLOT(rest()));
        predatorTimer->start(500);
    }
    /*Если голод падает ниже 10 каждую секунду теряет 5 хп*/
    if(hunger <= 10){
        qDebug() << "Predator with ID = " << GetUid() << " getting damage";
        get_damage();
    }

    if (processCollidings(colliding) == true) {
        eat();
    }

}
