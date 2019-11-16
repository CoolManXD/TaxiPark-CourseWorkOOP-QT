#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QListWidgetItem>

#include "taxiPark.h"
#include "map.h"
#include "driverMap.h"
#include "taxiPark.h"
#include "client.h"

//#include "busylistwindow.h"
class BusyListWindow;
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    friend class BusyListWindow;
private slots:

    void on_editSearchLocation_textChanged(const QString &);
    void on_editSearchDestination_textChanged(const QString &);
    void on_listLocation_itemClicked(); // QListWidgetItem *item
    void on_listDestination_itemClicked();

    void on_confirmButton_clicked();

    void on_actionBusyList_triggered();

private:
    Ui::MainWindow *ui;
    Map m_map;
    TaxiPark m_park;
    void refreshListOfSearch();

//    BusyListWindow *p;
//    QLabel *p2;

};

#endif // MAINWINDOW_H
