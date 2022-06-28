#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grass.h"
#include "hare.h"
#include <QApplication>
#include <cstdlib>
#include <ctime>
#include <QTimer>
#include <QDateTime>

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



    //Добавление травы на сцену
    grass = new Grass;
    grass->setPos(randomBetween(30,700,QDateTime::currentMSecsSinceEpoch())
                  ,randomBetween(10,300,QDateTime::currentMSecsSinceEpoch()));
    scene->addItem(grass);

    hare = new Hare;
    hare->setPos(randomBetween(30,700,QDateTime::currentSecsSinceEpoch())
                 ,randomBetween(10,300,QDateTime::currentSecsSinceEpoch()));
    scene->addItem(hare);

    timer = new QTimer;
    connect(timer,SIGNAL(timeout()),hare,SLOT(move()));
    timer->start(1000);


}

MainWindow::~MainWindow()
{
    delete ui;
}

