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
    explicit BusyListWindow(MainWindow *, TaxiPark *, QWidget *parent = nullptr);
    ~BusyListWindow();

private slots:
    void on_buttonUpdateTime_clicked();

    void closeEvent(QCloseEvent *event);

private:
    Ui::BusyListWindow *ui;
    MainWindow *m_mainwindow;
    TaxiPark *m_park;
    void updateBusyList();
};

#endif // BUSYLISTWINDOW_H
