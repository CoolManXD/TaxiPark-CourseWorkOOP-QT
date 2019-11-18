#ifndef ORDERWINDOW_H
#define ORDERWINDOW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class OrderWindow;
}

class OrderWindow : public QWidget
{
    Q_OBJECT

public:
    explicit OrderWindow(Map *, TaxiPark *, QWidget *parent = nullptr);
    ~OrderWindow();

private slots:

    void on_editSearchLocation_textChanged(const QString &);
    void on_editSearchDestination_textChanged(const QString &);
    void on_listLocation_itemClicked(); // QListWidgetItem *item
    void on_listDestination_itemClicked();

    void on_confirmButton_clicked();



private:
    Ui::OrderWindow *ui;
    Map *m_map;
    TaxiPark *m_park;

    void refreshListOfSearch();
};

#endif // ORDERWINDOW_H
