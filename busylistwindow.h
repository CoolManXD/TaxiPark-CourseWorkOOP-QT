#ifndef BUSYLISTWINDOW_H
#define BUSYLISTWINDOW_H

#include <QWidget>

//#include "taxiPark.h"
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
    void updateBusyList();

private slots:
    void on_buttonUpdateTime_clicked();

//    void closeEvent(QCloseEvent *event);

private:
    Ui::BusyListWindow *ui;
    TaxiPark *m_park;
};

#endif // BUSYLISTWINDOW_H
