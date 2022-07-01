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

    // Создаём палитру для тёмной темы оформления
    QPalette darkPalette;

    // Настраиваем палитру для цветовых ролей элементов интерфейса
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
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
    grass = new Grass[25];
    for(int i = 0; i<25;i++){
    grass[i].setPos(randomBetween(30,650,rand())
                  ,randomBetween(10,250,rand()));
    scene->addItem(&grass[i]);
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


    //Запуск таймера
    timer->start(500);

}

MainWindow::~MainWindow()
{
    delete ui;
}


