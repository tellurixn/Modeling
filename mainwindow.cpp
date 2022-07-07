#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grass.h"
#include "herbivores.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>
#include <QTimer>
#include <QDateTime>
#include <QVector>
#include <QLineEdit>

static int randomBetween(int low, int high, int seed)
{
    srand(seed);
    return (rand() % ((high + 1) - low) + low);
}


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->HareText->setText("0");
    ui->DeerText->setText("0");
    ui->WolfText->setText("0");
    // Создаём палитру для  темы оформления
    QPalette darkPalette;

    // Настраиваем палитру для цветовых ролей элементов интерфейса
    darkPalette.setColor(QPalette::Window, QColor(175, 218, 252));
    darkPalette.setColor(QPalette::WindowText, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Button, QColor(28, 169, 201));
    darkPalette.setColor(QPalette::ButtonText, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);


    // Устанавливаем данную палитру
    qApp->setPalette(darkPalette);

    //Подключение графической сцены
    scene = new QGraphicsScene();
    scene->setSceneRect(20,10,680,280);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->setScene(scene);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);//сглыживаем линии

    //Создание таймера для сцены
    timer = new QTimer;

    //Добавление травы на сцену
    for(int i = 0; i<45;i++){
    auto newGrass = new Grass();
    grass.push_back(newGrass);

    grass[i]->setPos(randomBetween(30,650,rand())
                  ,randomBetween(10,250,rand()));
    scene->addItem(grass[i]);
    }

    //Добвление зайцев на сцену
    for(int i = 0; i<5;i++){
    auto newHare = new Hare();
    hares.push_back(newHare);

    hares[i]->setPos(randomBetween(30,650,rand())
                    ,randomBetween(10,250,rand()));

    scene->addItem(hares[i]);

    //Коннект таймаута таймера со слотом status зайцев
    connect(timer,SIGNAL(timeout()),hares[i],SLOT(status()));
    }

    //Добвление оленей на сцену
    for(int i = 0; i<5;i++){
    auto newDeer = new Deer();
    deers.push_back(newDeer);

    deers[i]->setPos(randomBetween(30,650,rand())
                 ,randomBetween(10,250,rand()));

    scene->addItem(deers[i]);

    //Коннект таймаута таймера со слотом status оленей
    connect(timer,SIGNAL(timeout()),deers[i],SLOT(status()));
    }


    //Добвление хищников на сцену
    for(int i = 0; i<5;i++){
    auto newWolf = new Wolf();
    wolfs.push_back(newWolf);

    wolfs[i]->setPos(randomBetween(30,650,rand())
                 ,randomBetween(10,250,rand()));

    scene->addItem(wolfs[i]);

    //Коннект таймаута таймера со слотом status волков
    connect(timer,SIGNAL(timeout()),wolfs[i],SLOT(status()));
    connect(wolfs[i],SIGNAL(hareEaten()),this,SLOT(updateHareText()));
    connect(wolfs[i],SIGNAL(deerEaten()),this,SLOT(updateDeerText()));
    connect(wolfs[i],SIGNAL(wolfDead()),this,SLOT(updateWolfText()));
    }

//   Запуск таймера
//    timer->start(250);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateHareText()
{
   QString old = ui->HareText->text();

   int newVal = old.toInt() + 1;

   QString NEWVAL = QString::number(newVal);

   ui->HareText->setText(NEWVAL);
}

void MainWindow::updateDeerText()
{
    QString old = ui->DeerText->text();

    int newVal = old.toInt() + 1;

    QString NEWVAL = QString::number(newVal);

    ui->DeerText->setText(NEWVAL);
}

void MainWindow::updateWolfText()
{
    QString old = ui->WolfText->text();

    int newVal = old.toInt() + 1;

    QString NEWVAL = QString::number(newVal);

    ui->WolfText->setText(NEWVAL);
}

void MainWindow::on_addGrassButton_clicked()
{
    auto newGrass = new Grass();
    grass.push_back(newGrass);
    int last = grass.size() - 1;

    grass[last]->setPos(randomBetween(30,650,rand())
                  ,randomBetween(10,250,rand()));
    scene->addItem(grass[last]);

}

void MainWindow::on_addHareButton_clicked()
{
    auto newHare = new Hare();
    hares.push_back(newHare);
    int last = hares.size() - 1;

    hares[last]->setPos(randomBetween(30,650,rand())
                  ,randomBetween(10,250,rand()));
    scene->addItem(hares[last]);

    connect(timer,SIGNAL(timeout()),hares[last],SLOT(status()));
}

void MainWindow::on_addDeerButton_clicked()
{
    auto newDeer = new Deer();
    deers.push_back(newDeer);
    int last = deers.size() - 1;

    deers[last]->setPos(randomBetween(30,650,rand())
                  ,randomBetween(10,250,rand()));
    scene->addItem(deers[last]);

    //Коннект таймаута таймера со слотом status оленей
    connect(timer,SIGNAL(timeout()),deers[last],SLOT(status()));
}

void MainWindow::on_addWolfButton_clicked()
{
    auto newWolf = new Wolf();
    wolfs.push_back(newWolf);

    int last = wolfs.size() - 1;
    wolfs[last]->setPos(randomBetween(30,650,rand())
                 ,randomBetween(10,250,rand()));

    scene->addItem(wolfs[last]);

    //Коннект таймаута таймера со слотом status волков
    connect(timer,SIGNAL(timeout()),wolfs[last],SLOT(status()));
    connect(wolfs[last],SIGNAL(hareEaten()),this,SLOT(updateHareText()));
    connect(wolfs[last],SIGNAL(deerEaten()),this,SLOT(updateDeerText()));
    connect(wolfs[last],SIGNAL(wolfDead()),this,SLOT(updateWolfText()));
}


void MainWindow::on_Play_clicked()
{
    //Запуск таймера
    timer->start(250);
}


void MainWindow::on_Pause_clicked()
{
    timer->stop();
}

