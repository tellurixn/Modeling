#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grass.h"
#include "hare.h"
#include <QApplication>
#include <cstdlib>

static int randomBetween(int low, int high)
{
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
    ui->graphicsView->setScene(scene);

    //Добавление травы на сцену
    grass = new Grass;
    grass->setPos(randomBetween(30,700),randomBetween(10,300));
    scene->addItem(grass);

    hare = new Hare;
    hare->setPos(randomBetween(30,700),randomBetween(10,300));
    scene->addItem(hare);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);//сглыживаем линии
}

MainWindow::~MainWindow()
{
    delete ui;
}

