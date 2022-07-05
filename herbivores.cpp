#include "herbivores.h"
#include "grass.h"
#include "mainwindow.h"
#include "qgraphicsscene.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <QApplication>
#include <QDateTime>
#include <QVector2D>
#include <QTimer>

int Herbivores::newUID = 0;

static int randomBetween(int low, int high, int seed)
{
    srand(seed);
    return (rand() % ((high + 1) - low) + low);
}

/*Конструктор по умолчанию*/
Herbivores::Herbivores(QObject *parent) : QObject(parent)  , uid(newUID++)
{

    hunger = 100;
    stamina = 100;
    hp = 100;
}

/*Деструктор*/
Herbivores::~Herbivores()
{


}

/*Обнаружение коллизий*/
bool Herbivores::processCollidings(QList<QGraphicsItem *> collidins)
{
    bool can_eat = false;
      for (QGraphicsItem* item: collidins) {
        if (dynamic_cast<Grass*> (item)){
          can_eat = true;

          this->lastFood.setX(this->pos().x());
          this->lastFood.setY(this->pos().y());
        }
      }
      return can_eat;
}

/*Получить ID объекта*/
int Herbivores::GetUid()
{
    return uid;
}

/*Отрисовка на графической сцене*/
void Herbivores::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::NoPen);

    painter->setBrush(QColor(Qt::green));

    painter->drawEllipse(0,0,20,20);


}

/*Возращение формы - прямоугольника*/
QRectF Herbivores::boundingRect() const
{
    return QRectF(0,0,20,20);
}


/*Покоиться*/
void Herbivores::rest()
{
    if (stamina<100){
      //  qDebug() << "Herbivores is resting now, stamina = " << stamina
         //        << " HP = " << hp << " Hunger = " << hunger;
        stamina += 1;
        hunger -= 0.5;
        if (hunger<=0)
            hunger = 0;
    }
    else{
        delete HerbivoresTimer;//удаление таймера
        HerbivoresTimer = nullptr;//присвоить nullptr
    }
}

/*Получать урон*/
void Herbivores::get_damage()
{
    if(hp>=5)
        hp -= 5;
    else{
        hp = 0;
       // qDebug() << "Herbivores ID" << GetUid()<< " is dead.";
        this->deleteLater();
    }
}

/*Кушать*/
void Herbivores::eat()
{
    if (hunger < 100){
        hunger += 20;
        stamina += 15;
        hp += 25;

        if(hunger>100)
            hunger = 100;
        if(stamina>100)
            stamina = 100;
        if(hp>100)
            hp = 100;

    }
    else{
        delete HerbivoresTimer;//удаление таймера
        HerbivoresTimer = nullptr;//присвоить nullptr
    }
}

/*Двигаться к месту последнего приема пищи*/
void Herbivores::moveForFood()
{
    QVector2D v1(pos().x(),pos().y());
    QVector2D v2(lastFood.x(),lastFood.y());
    if(v1.distanceToPoint(v2) != 0){
       //  qDebug() << "Herbivores is moving for food now, stamina = " << stamina
           //       << " HP = " << hp << " Hunger = " << hunger;
        if(v1.x()!= v2.x()){
            if(v2.x()<v1.x())
                setX(pos().x() - 1);
            else
                setX(pos().x() + 1);
        }
        if(v1.y()!=v2.y()){
            if(v2.y()<v1.y())
                setY(pos().y() - 1);
            else
                setY(pos().y() + 1);
        }

        stamina -=0.2;
        hunger -= 0.2;
        if (hunger<=0)
            hunger = 0;
    }
    else{
        delete HerbivoresTimer;//удаление таймера
        HerbivoresTimer = nullptr;//присвоить nullptr
    }
}

/*Передвигаться(рандомно)*/
void Herbivores::move()
{

    /*Рандомные новые координаты*/
    QPointF newPos = QPointF(pos().x() + randomBetween(-10,10,rand()),
                             pos().y() + randomBetween(-10,10,rand()));

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

/*Постоянный опрос объекта о его статусе*/
void Herbivores::status(){
    int random = randomBetween(50,85,rand());


    /*двигаться если стамина больше 50 и заяц не отдыхает*/
    if(stamina >=random && HerbivoresTimer == nullptr){
       // qDebug() << "Herbivores is moving now, stamina = " << stamina
         //        << " HP = " << hp << " Hunger = " << hunger;
        emit move();

    }
    /*отдых если стамина меньше 50*/
    if(stamina < random){
        HerbivoresTimer = new QTimer;
        connect(HerbivoresTimer,SIGNAL(timeout()),this,SLOT(rest()));
        HerbivoresTimer->start(500);
    }
    /*Если голод падает ниже 10 каждую секунду теряет 5 хп*/
    if(hunger <= 10){
       // qDebug() << "Herbivores is getting damage now, hp = "
         //       << hp << " Hunger = " << hunger;
        emit get_damage();
    }

    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    if (processCollidings(colliding) == true && hunger <=50) {
        HerbivoresTimer = new QTimer;
        connect(HerbivoresTimer,SIGNAL(timeout()),this,SLOT(eat()));
        HerbivoresTimer->start(500);
    }
    if (hunger <=50 && lastFood.isNull() == false){
        HerbivoresTimer = new QTimer;
        connect(HerbivoresTimer,SIGNAL(timeout()),this,SLOT(moveForFood()));
        HerbivoresTimer->start(500);
    }



}
