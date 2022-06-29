#include "hare.h"
#include "grass.h"
#include "qgraphicsscene.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>
#include <QApplication>
#include <QTimer>
#include <QDateTime>
#include <QVector2D>

static int randomBetween(int low, int high, int seed)
{
    srand(seed);
    return (rand() % ((high + 1) - low) + low);
}

/*Конструктор по умолчанию*/
Hare::Hare() : QObject(), QGraphicsItem(){
    srand(time(NULL));

    char gndr[2]={'m','f'};
    int random = rand()%2;
    gender = gndr[random];

    hunger = 100;
    stamina = 100;
    age = 0;
    hp = 100;

    hareTimer = nullptr;

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

/*Отрисовка на графической сцене*/
void Hare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    painter->setPen(Qt::NoPen);

    if(gender == 'm'){
        painter->setBrush(QColor(128,128,128));
    }
    else{
        painter->setBrush(QColor(Qt::white));
    }

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
        qDebug() << "Hare is resting now, stamina = " << this->stamina
                 << " HP = " << this->hp << " Hunger = " << this->hunger;
        this->stamina +=5;
        this->hunger -2;
        if (this->hunger<=0)
            this->hunger = 0;
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
        this->hp -= 5;
    else
        this->deleteLater();//Заяц умирает при уровне здоровья 0
}

void Hare::eat()
{
    if (this->hunger < 100 || this->hp <100){
        this->hunger += 20;
        this->stamina += 15;
        this->hp += 25;

        if(this->hunger > 100)
            this->hunger = 100;
        if(this->stamina > 100)
            this->stamina = 100;
        if(this->hp > 100)
            this->hp = 100;

    }
    else{

        delete hareTimer;//удаление таймера
        hareTimer = nullptr;//присвоить nullptr
    }
}

void Hare::moveForFood()
{
    QVector2D v1(this->pos().x(),this->pos().y());
    QVector2D v2(this->lastFood.x(),this->lastFood.y());
    if(v1.distanceToPoint(v2) != 0){
         qDebug() << "Hare is moving for food now, stamina = " << this->stamina
                  << " HP = " << this->hp << " Hunger = " << this->hunger;
        if(v1.x()!= v2.x()){
            if(v2.x()<v1.x())
                this->setX(this->pos().x() - 1);
            else
                this->setX(this->pos().x() + 1);
        }
        if(v1.y()!=v2.y()){
            if(v2.y()<v1.y())
                this->setY(this->pos().y() - 1);
            else
                this->setY(this->pos().y() + 1);
        }
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
    QPointF newPos = QPointF(this->pos().x() + randomBetween(-20,20,QDateTime::currentMSecsSinceEpoch()), this->pos().y() + randomBetween(-20,20,QDateTime::currentSecsSinceEpoch()));

    /*Ограничение по координатам
    для предотвращения выхода за границы*/
    if(this->pos().x()>=700 || this->pos().y()>=300){
        newPos.setX(this->pos().x() - 30);
        newPos.setY(this->pos().y() - 10);

    }
    else if(this->pos().x()<=30 || this->pos().y()<=10){
        newPos.setX(this->pos().x() + 30);
        newPos.setY(this->pos().y() + 10);
    }

    //установка новой позиции
    this->setPos(newPos);
    this->stamina -=5;
    this->hunger-=2;
    if (this->hunger<=0)
        this->hunger = 0;

}

/*Постоянный опрос объекта о его статусе*/
void Hare::status(){
    /*двигаться если стамина больше 50 и заяц не отдыхает*/
    if(stamina >=50 && hareTimer == nullptr){
        qDebug() << "Hare is moving now, stamina = " << this->stamina
                 << " HP = " << this->hp << " Hunger = " << this->hunger;
        emit this->move();

    }
    /*отдых если стамина меньше 50*/
    if(this->stamina <=49){
        hareTimer = new QTimer;
        connect(hareTimer,SIGNAL(timeout()),this,SLOT(rest()));
        hareTimer->start(1000);
    }
    /*Если голод падает ниже 10 заяц каждую секунду теряет 5 хп*/
    if(this->hunger <= 10){
        qDebug() << "Hare is getting damage now, hp = "
                 << this->hp << " Hunger = " << this->hunger;
        emit this->get_damage();
    }

    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    if (processCollidings(colliding) == true && this->hunger <=50) {
        hareTimer = new QTimer;
        connect(hareTimer,SIGNAL(timeout()),this,SLOT(eat()));
        hareTimer->start(1000);
    }
    if (this->hunger <=55 && this->lastFood.isNull() == false){
        hareTimer = new QTimer;
        connect(hareTimer,SIGNAL(timeout()),this,SLOT(moveForFood()));
        hareTimer->start(1000);
    }


}
