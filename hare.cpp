#include "hare.h"
#include "grass.h"
#include "mainwindow.h"
#include "qgraphicsscene.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>
#include <QApplication>
#include <QTimer>
#include <QDateTime>
#include <QVector2D>

int Hare::newUID = 0;
static int randomBetween(int low, int high, int seed)
{
    srand(seed);
    return (rand() % ((high + 1) - low) + low);
}

/*Конструктор по умолчанию*/
/*Hare::Hare() : QObject(), QGraphicsItem(){
    srand(time(NULL));

    char gndr[2]={'m','f'};
    int random = randomBetween(0,1,rand());
    gender = &gndr[random];

    hunger = 100;
    stamina = 100;
    age = 0;
    hp = 100;

    hareTimer = nullptr;

}*/

Hare::Hare(QObject *parent) : QObject(parent)  , uid(newUID++)
{

    hunger = 100;
    stamina = 100;
    age = 0;
    hp = 100;
}

Hare::~Hare()
{


}

bool Hare::processCollidings(QList<QGraphicsItem *> collidins)
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

int Hare::GetUid()
{
    return uid;
}

/*Отрисовка на графической сцене*/
void Hare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::NoPen);

    painter->setBrush(QColor(Qt::white));

    painter->drawEllipse(0,0,10,10);

}

/*Возращение формы - прямоугольника*/
QRectF Hare::boundingRect() const
{
    return QRectF(0,0,10,10);
}

/*Возращение формы - эллипса*/
QPainterPath Hare::shape() const
{
    /*Функция возращает форму зайца в виде эллипса*/
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;
}


/*Покоиться*/
void Hare::rest()
{
    if (stamina<100){
        qDebug() << "Hare is resting now, stamina = " << stamina
                 << " HP = " << hp << " Hunger = " << hunger;
        stamina +=5;
        hunger -=20;
        if (hunger<=0)
            hunger = 0;
    }
    else{
        delete hareTimer;//удаление таймера
        hareTimer = nullptr;//присвоить nullptr
    }
}

/*Получать урон*/
void Hare::get_damage()
{
    if(hp>=5)
        hp -= 5;
    else{
        hp = 0;
        qDebug() << "Hare ID" << GetUid()<< " is dead.";
        this->deleteLater();
    }
}

void Hare::eat()
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
        delete hareTimer;//удаление таймера
        hareTimer = nullptr;//присвоить nullptr
    }
}

void Hare::moveForFood()
{
    QVector2D v1(pos().x(),pos().y());
    QVector2D v2(lastFood.x(),lastFood.y());
    if(v1.distanceToPoint(v2) != 0){
         qDebug() << "Hare is moving for food now, stamina = " << stamina
                  << " HP = " << hp << " Hunger = " << hunger;
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

        stamina -=2;
        hunger-=2;
        if (hunger<=0)
            hunger = 0;
    }
    else{
        delete hareTimer;//удаление таймера
        hareTimer = nullptr;//присвоить nullptr
    }
}

/*Передвигаться(рандомно)*/
void Hare::move()
{

    /*Рандомные новые координаты*/
    QPointF newPos = QPointF(pos().x() + randomBetween(-20,20,rand()), pos().y() + randomBetween(-20,20,rand()));

    /*Ограничение по координатам
    для предотвращения выхода за границы*/
    if(pos().x()>=700 || pos().y()>=300){
        newPos.setX(pos().x() - 30);
        newPos.setY(pos().y() - 10);

    }
    else if(pos().x()<=30 || pos().y()<=10){
        newPos.setX(pos().x() + 30);
        newPos.setY(pos().y() + 10);
    }

    //установка новой позиции
    setPos(newPos);
    stamina -=5;
    hunger-=5;
    if (hunger<=0)
        hunger = 0;

}

/*Постоянный опрос объекта о его статусе*/
void Hare::status(){
    int random = randomBetween(50,85,rand());


    /*двигаться если стамина больше 50 и заяц не отдыхает*/
    if(stamina >=random && hareTimer == nullptr){
        qDebug() << "Hare is moving now, stamina = " << stamina
                 << " HP = " << hp << " Hunger = " << hunger;
        emit move();

    }
    /*отдых если стамина меньше 50*/
    if(stamina < random){
        hareTimer = new QTimer;
        connect(hareTimer,SIGNAL(timeout()),this,SLOT(rest()));
        hareTimer->start(1000);
    }
    /*Если голод падает ниже 10 заяц каждую секунду теряет 5 хп*/
    if(hunger <= 10){
        qDebug() << "Hare is getting damage now, hp = "
                 << hp << " Hunger = " << hunger;
        emit get_damage();
    }

    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    if (processCollidings(colliding) == true && hunger <=50) {
        hareTimer = new QTimer;
        connect(hareTimer,SIGNAL(timeout()),this,SLOT(eat()));
        hareTimer->start(1000);
    }
    if (hunger <=50 && lastFood.isNull() == false){
        hareTimer = new QTimer;
        connect(hareTimer,SIGNAL(timeout()),this,SLOT(moveForFood()));
        hareTimer->start(500);
    }



}
