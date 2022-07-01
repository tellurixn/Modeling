#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include "grass.h"
#include "hare.h"
#include <vector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }

QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene; //график сцена
    QTimer *timer;
    Grass *grass;//объект класса трава
    std::vector <Hare*> hares; //вектор объектов класса заяц


};
#endif // MAINWINDOW_H
