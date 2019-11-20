#include "busylistwindow.h"
#include "ui_busylistwindow.h"
#include "mainwindow.h"
#include <QString>

BusyListWindow::BusyListWindow(TaxiPark *park, QWidget *parent) :
    m_park(park),
    QWidget(parent),
    ui(new Ui::BusyListWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);

    updateBusyList();
}

BusyListWindow::~BusyListWindow()
{
    delete ui;
}

// обновление списков и времени до особождения водителей
void BusyListWindow::updateBusyList()
{
    ui->listFreeDrivers->clear();
    ui->treeBusyDrivers->clear();

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    for (auto it = m_park->driversDependent.begin(); it != m_park->driversDependent.end(); ++it) // перебор зависимых водителей
    {
        if (it->isBusy()) // если занят
        {
            //определение интервала времени между начальным timepoint и текущим
            //если интервал больше времени поездки, то водителю ставим статус free и добавляем в free список
            if (std::chrono::duration_cast<std::chrono::seconds>(endTime - it->getStartTime()).count() >= it->getBusyTime())
            {
                it->changeIsBusy();
                ui->listFreeDrivers->addItem(it->getName());
            }
            //иначе добавляем в busy список с временем до конца поездки
            else
            {
                QTreeWidgetItem *item = new QTreeWidgetItem();
                item->setText(0, it->getName());
                item->setText(1,QString::number(int(it->getBusyTime() - std::chrono::duration_cast<std::chrono::seconds>(endTime - it->getStartTime()).count())));
                ui->treeBusyDrivers->addTopLevelItem(item);
            }
        }
        else //если водитель свободный изначально добавляем в free список
        {
            ui->listFreeDrivers->addItem(it->getName());
        }
    }

    for (auto it = m_park->driversIndependent.begin(); it != m_park->driversIndependent.end(); ++it) // перебор независимых водителей
    {
        if (it->isBusy()) // если занят
        {
            //определение интервала времени между начальным timepoint и текущим
            //если интервал больше времени поездки, то водителю ставим статус free и добавляем в free список
            if (std::chrono::duration_cast<std::chrono::seconds>(endTime - it->getStartTime()).count() >= it->getBusyTime())
            {
                it->changeIsBusy();
                ui->listFreeDrivers->addItem(it->getName());
            }
            //иначе добавляем в busy список с временем до конца поездки
            else
            {
                QTreeWidgetItem *item = new QTreeWidgetItem();
                item->setText(0, it->getName());
                item->setText(1,QString::number(it->getBusyTime() - std::chrono::duration_cast<std::chrono::seconds>(endTime - it->getStartTime()).count()));
                ui->treeBusyDrivers->addTopLevelItem(item);
            }
        }
        else //если водитель свободный изначально добавляем в free список
        {
            ui->listFreeDrivers->addItem(it->getName());
        }
    }
}

//при нажатие на кнопку update
void BusyListWindow::on_buttonUpdateTime_clicked()
{
    updateBusyList();
}

//void BusyListWindow::closeEvent(QCloseEvent *event)
//{
//    m_mainwindow->show();
//    event->accept();
//}
