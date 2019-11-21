#ifndef FINANCIALWINDOW_H
#define FINANCIALWINDOW_H

#include <QWidget>
#include "mainwindow.h"

namespace Ui {
class FinancialWindow;
}

class FinancialWindow : public QWidget
{
    Q_OBJECT

public:
    explicit FinancialWindow(TaxiPark *, QWidget *parent = nullptr);
    ~FinancialWindow();

    void updateListSalary();

private slots:
    void on_buttonPaySalary_clicked();

private:
    Ui::FinancialWindow *ui;
    TaxiPark *m_park;
    QStringListModel *m_model;
};

#endif // FINANCIALWINDOW_H
