#ifndef INFODRIVERSWINDOW_H
#define INFODRIVERSWINDOW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class InfoDriversWindow;
}

class InfoDriversWindow : public QWidget
{
    Q_OBJECT

public:
    explicit InfoDriversWindow(TaxiPark *, QWidget *parent = nullptr);
    ~InfoDriversWindow();

    void loadInfoView();

private slots:
    void on_listDependentDrivers_clicked(const QModelIndex &index);

    void on_listIndependentDrivers_clicked(const QModelIndex &index);

private:
    Ui::InfoDriversWindow *ui;
    TaxiPark *m_park;
    QStringListModel *m_model_Dependent;
    QStringListModel *m_model_Independent;
};

#endif // INFODRIVERSWINDOW_H
