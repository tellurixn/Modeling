#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QGraphicsScene>
#include "grass.h"
#include "hare.h"
#include "deer.h"
#include "wolf.h"
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
public slots:
    void updateHareText();//обновить кол-во умерших зайцев
    void updateDeerText();//                        оленей
    void updateWolfText();//                        волков
private slots:
    void on_addGrassButton_clicked();//кнопка добавления травы

    void on_addHareButton_clicked();//кнопка добавления зайца

    void on_addDeerButton_clicked();//кнопка добавления оленя

    void on_addWolfButton_clicked();//кнопка добавления волка

private:
    Ui::MainWindow *ui;//интерфейс
    QGraphicsScene *scene; //графическая сцена
    QTimer *timer;//таймер сцены
    std::vector <Grass*> grass;;//объект класса трава
    std::vector <Hare*> hares; //вектор объектов класса заяц
    std::vector <Deer*> deers; //вектор объектов класса олень
    std::vector <Wolf*> wolfs; //вектор объектов класса волк



};
#endif // MAINWINDOW_H
