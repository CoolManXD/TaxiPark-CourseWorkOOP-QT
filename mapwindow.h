#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <QWidget>
//#include <QStringListModel>
#include "mainwindow.h"

namespace Ui {
class MapWindow;
}

class MapWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MapWindow(TaxiPark *, QWidget *parent = nullptr);
    ~MapWindow();

    void updateWaysView();

private:
    Ui::MapWindow *ui;
    TaxiPark *m_park;
    QStringListModel *m_model;
};

#endif // MAPWINDOW_H
