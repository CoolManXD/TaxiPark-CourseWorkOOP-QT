#include "mainwindow.h"

#include "ui_mainwindow.h"
#include "busylistwindow.h"
#include "orderwindow.h"
#include "mapwindow.h"
#include "infodriverswindow.h"
#include "financialwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_park.setDriverMap(new DriverMap{ m_map }); // присвоить статическому элементу карту для класса Driver

    setCentralWidget(ui->stackedWidget);
    orderWindow = new OrderWindow(&m_map, &m_park);
    busyListWindow = new BusyListWindow(&m_park);
    mapWindow = new MapWindow(&m_park);
    infoDriversWindow = new InfoDriversWindow(&m_park);
    financialWindow = new FinancialWindow(&m_park);

    ui->stackedWidget->insertWidget(0, orderWindow);
    ui->stackedWidget->insertWidget(1, busyListWindow);
    ui->stackedWidget->insertWidget(2, mapWindow);
    ui->stackedWidget->insertWidget(3, infoDriversWindow);
    ui->stackedWidget->insertWidget(4, financialWindow);

    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    m_park.saveFinancialInfo(); // сохранить в файлы финансы компании и з/п водителей
    delete ui;
}

//---------------Открытие виджетов-----------------
void MainWindow::on_actionOrder_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}
void MainWindow::on_actionBusyList_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    busyListWindow->updateBusyList();
}
void MainWindow::on_actionMapTown_triggered()
{
    ui->stackedWidget->setCurrentIndex(2);
    mapWindow->updateWaysView();
}
void MainWindow::on_actionactionInfoDrivers_triggered()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_actionFinance_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
    financialWindow->updateListSalary();
}
