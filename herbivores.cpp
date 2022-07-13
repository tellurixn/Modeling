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

static int randomBetween(int low, int high, int seed)
{
    srand(seed);
    return (rand() % ((high + 1) - low) + low);
}

/*Конструктор по умолчанию*/
Herbivores::Herbivores(QObject *parent) : QObject(parent)
{
    hunger = 100;
    stamina = 100;
    hp = 100;
    HerbivoresTimer = nullptr;

    /*Берем рандомную точку на сцене*/
    newPosition = QPointF(randomBetween(30,650,rand()),randomBetween(10,250,rand()));
   // qDebug() << "Construcror's  newPos = (" << newPosition.x() << ", "<< newPosition.y() <<")";
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
        if (dynamic_cast<Grass*> (item)){//если наткнулся на объект класса Grass
          can_eat = true; //можно есть

          /*Запомнить координаты травы*/
          this->lastFood.setX(this->pos().x());
          this->lastFood.setY(this->pos().y());
        }
      }
      return can_eat;
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
        stamina += 1;//пока отдыхает восстанавливается выносливость
        hunger -= 0.25;//растет голод
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
    if(hp>=2)
        hp -= 2;
    else{
        hp = 0;
        this->deleteLater();
    }
}

/*Кушать*/
void Herbivores::eat()
{
    if (hunger < 100){
        hunger += 20;//пока ест голод уменьшается
        stamina += 10;//восстанавливается выносливость
        hp += 25;//восстанавливается здоровье

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
    QVector2D v1(pos().x(),pos().y()); //вектор - текущее положение
    QVector2D v2(lastFood.x(),lastFood.y());//вектор - положение еды

    if(v1.distanceToPoint(v2) != 0){ //проверка расстояния до еды

        if(v1.x()!= v2.x()){ //если по OX не совпадает
            if(v2.x()<v1.x()) //и еда левее
                setX(pos().x() - 1);//сместиться влево
            else
                setX(pos().x() + 1);//иначе сместиться правее
        }
        if(v1.y()!=v2.y()){ //если по OY не совпадает
            if(v2.y()<v1.y())//и еда выше
                setY(pos().y() - 1);//подняться
            else
                setY(pos().y() + 1);//иначе опуститься по OY
        }

        stamina -=0.2;//пока идет к еде теряет очки выносливости
        hunger -= 0.2;//и очки голода
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
    /*К выбранной рандомной точке прокладывается прямая
    движение происходит по уравнению прямой через 2 точки*/

    //если еще не сместился на другой конец прямой
    if(pos().x() != newPosition.x() && pos().y()!= newPosition.y()){

    if(newPosition.x() < pos().x()){ //если точка левее уменьшаем x на 1 каждый шаг
        double oldX = pos().x(),//старые
            oldY = pos().y();//координаты

        double newX = oldX - 1,//новый икс
           //новый игрек
           newY = ((newX - oldX)*(newPosition.y()-oldY))/(newPosition.x() - oldX) + oldY;

        setPos(newX,newY);
    }
    else{ //если точка правее прибавляем к иксу единицу каждый шаг
        double oldX = pos().x(),//старые
               oldY = pos().y();//координаты

        double newX = oldX + 1,//новый икс
               //новый игрек
               newY = ((newX - oldX)*(newPosition.y()-oldY))/(newPosition.x() - oldX) + oldY;

        setPos(newX,newY);
        }
    }
    else{
        //новая точка выбирается когда закончил передвижение по предыдущей прямой
        newPosition = QPointF(randomBetween(30,650,rand()),randomBetween(10,250,rand()));
    }

    stamina -=0.25;//за шаш выносливость -0.25
    hunger -= 0.25;//голод -0.25
    if (hunger<=0)
        hunger = 0;

}

/*Постоянный опрос объекта о его статусе*/
void Herbivores::status(){
    int random = randomBetween(50,85,rand());


    /*двигаться если стамина больше 50 и заяц не отдыхает*/
    if(stamina >=random && HerbivoresTimer == nullptr){
        emit move();
    }

    /*отдых если стамина меньше 50*/
    if(stamina < random){
        HerbivoresTimer = new QTimer;
        connect(HerbivoresTimer,SIGNAL(timeout()),this,SLOT(rest()));
        HerbivoresTimer->start(250);
    }

    /*Если голод падает ниже 10 каждую секунду теряет 5 хп*/
    if(hunger <= 10){
        emit get_damage();
    }

    QList<QGraphicsItem *> colliding = scene()->collidingItems(this);

    /*Если обнаружил объект который можно съесть
    и голод ниже 50, то съесть этот объект*/
    if (processCollidings(colliding) == true && hunger <=50) {
        HerbivoresTimer = new QTimer;
        connect(HerbivoresTimer,SIGNAL(timeout()),this,SLOT(eat()));
        HerbivoresTimer->start(250);
    }

    /*Если голод ниже 50 и объект уже ел когда-то
    двигаться к этому объекту*/
    if (hunger <=50 && lastFood.isNull() == false){
        HerbivoresTimer = new QTimer;
        connect(HerbivoresTimer,SIGNAL(timeout()),this,SLOT(moveForFood()));
        HerbivoresTimer->start(250);
    }


}
