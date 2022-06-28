#include "hare.h"
#include "grass.h"
#include "qgraphicsscene.h"
#include <QGraphicsEllipseItem>
#include <cstdlib>
#include <ctime>
#include <QApplication>
#include <QTimer>
#include <QDateTime>

static int randomBetween(int low, int high, int seed)
{
    srand(seed);
    return (rand() % ((high + 1) - low) + low);
}

Hare::Hare() : QObject(), QGraphicsItem(){
    srand(time(NULL));

    char gndr[2]={'m','f'};
    int random = rand()%2;
    gender = gndr[random];

    hunger = 100;
    stamina = 100;
    age = 0;

}



void Hare::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);

    if(gender == 'm'){
        painter->setBrush(QColor(128,128,128));
    }
    else{
        painter->setBrush(QColor(Qt::white));
    }

    painter->drawEllipse(0,0,10,10);

    Q_UNUSED(option)
    Q_UNUSED(widget)

}

QRectF Hare::boundingRect() const
{
    return QRectF(0,0,10,10);
}

QPainterPath Hare::shape() const
{
    /*Функция возращает форму зайца в виде эллипса*/
    QPainterPath path;
    path.addEllipse(boundingRect());
    return path;

}

void Hare::debug()
{
    qDebug() << "Slot is working";

}

void Hare::move()
{
    QPointF oldPos = this->pos();
    QPointF newPos;

    newPos= QPointF(this->pos().x() + randomBetween(-20,20,QDateTime::currentMSecsSinceEpoch()), this->pos().y() + randomBetween(-20,20,QDateTime::currentSecsSinceEpoch()));

    if(this->pos().x()>=700 || this->pos().y()>=300){
        newPos.setX(this->pos().x() - 30);
        newPos.setY(this->pos().y() - 10);

    }
    else if(this->pos().x()<=30 || this->pos().y()<=10){
        newPos.setX(this->pos().x() + 30);
        newPos.setY(this->pos().y() + 10);
    }

     this->setPos(newPos);
}
