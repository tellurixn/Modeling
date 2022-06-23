#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "MyGraphicView.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    MyScene = new MyGraphicView();
    ui->gridLayout->addWidget(MyScene);
}

MainWindow::~MainWindow()
{
    delete ui;
}

