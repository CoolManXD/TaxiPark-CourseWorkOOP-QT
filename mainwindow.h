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

    void on_editSearchL_textChanged(const QString &);
    void on_editSearchD_textChanged(const QString &);
    void on_listL_itemClicked(); // QListWidgetItem *item
    void on_listD_itemClicked();

    void on_confirmButton_clicked();

private:
    Ui::MainWindow *ui;
    Map m_map;
    TaxiPark m_park;
    void refreshListOfSearch();
};

#endif // MAINWINDOW_H
