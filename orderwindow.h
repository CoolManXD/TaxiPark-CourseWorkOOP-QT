// виджет с формой для принятия заказа от клиента
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
    void on_editSearchLocation_textChanged(const QString &); //поиск location в списке при вводе даных в поисковую строку
    void on_editSearchDestination_textChanged(const QString &); //поиск destination в списке при вводе даных в поисковую строку
    void on_listLocation_itemClicked(); // при выборе location удалить выбраный элемент в destination списке
    void on_listDestination_itemClicked(); // при выборе destination удалить выбраный элемент в location списке

    void on_confirmButton_clicked(); // обработка заказа

private:
    Ui::OrderWindow *ui;
    Map *m_map;
    TaxiPark *m_park;

    void refreshListOfSearch(); // очистить поисковые строки и unselect элементы в списках
};

#endif // ORDERWINDOW_H
