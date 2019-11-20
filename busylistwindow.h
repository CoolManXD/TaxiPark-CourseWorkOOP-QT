// виджет с списком зайнятости водителей
#ifndef BUSYLISTWINDOW_H
#define BUSYLISTWINDOW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class BusyListWindow;
}

class BusyListWindow : public QWidget
{
    Q_OBJECT

public:
    explicit BusyListWindow(TaxiPark *, QWidget *parent = nullptr);
    ~BusyListWindow();

    void updateBusyList(); // обновить списки, время до особождения водителей

private slots:
    void on_buttonUpdateTime_clicked(); // вызов с помощю кнопки updateBusyList()
//    void closeEvent(QCloseEvent *event);

private:
    Ui::BusyListWindow *ui;
    TaxiPark *m_park;
};

#endif // BUSYLISTWINDOW_H
