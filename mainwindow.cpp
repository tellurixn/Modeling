#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "grass.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);

    grass = new Grass;
    scene->addItem(grass);
}

MainWindow::~MainWindow()
{
    delete ui;
}

