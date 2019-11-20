#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "busylistwindow.h"
#include "orderwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_park.setDriverMap(new DriverMap{ m_map });
    setCentralWidget(ui->stackedWidget);
    orderWindow = new OrderWindow(&m_map, &m_park);
    busyListWindow = new BusyListWindow(&m_park);


    ui->stackedWidget->insertWidget(0, orderWindow);
    ui->stackedWidget->insertWidget(1, busyListWindow);
//    ui->stackedWidget->addWidget(orderWindow);
//    ui->stackedWidget->addWidget(busyListWindow);

    ui->stackedWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

//---------------открыть окно с списком зайнятости водителей-----------------
void MainWindow::on_actionBusyList_triggered()
{
    ui->stackedWidget->setCurrentIndex(1);
    busyListWindow->updateBusyList();
}


void MainWindow::on_actionOrder_triggered()
{
    ui->stackedWidget->setCurrentIndex(0);
}
