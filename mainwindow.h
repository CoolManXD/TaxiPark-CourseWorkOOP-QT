//Главное окно с контейнером для других кастомных виджетов
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QListWidgetItem>

#include "taxiPark.h"
#include "map.h"
#include "driverMap.h"
#include "client.h"

class BusyListWindow;
class OrderWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionOrder_triggered(); // открыть виджет с окном формы для принятия заказа от клиента
    void on_actionBusyList_triggered(); // открыть виджет с списком зайнятости водителей

private:
    Ui::MainWindow *ui;
    Map m_map;
    TaxiPark m_park;

    BusyListWindow *busyListWindow;
    OrderWindow *orderWindow;
};

#endif // MAINWINDOW_H
