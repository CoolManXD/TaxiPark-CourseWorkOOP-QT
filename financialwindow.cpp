#include "financialwindow.h"
#include "ui_financialwindow.h"

FinancialWindow::FinancialWindow(TaxiPark *park, QWidget *parent) :
    m_park(park),
    QWidget(parent),
    ui(new Ui::FinancialWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);

    m_model = new QStringListModel(this);
    updateListSalary();
}

FinancialWindow::~FinancialWindow()
{
    delete ui;
}

void FinancialWindow::updateListSalary()
{
    QStringList list;
    list << "Company finance: " + QString::number(m_park->getCompanyMoney()) + "$";
    for(auto it = m_park->getDependentDrivers().begin(); it != m_park->getDependentDrivers().end() ; ++it)
    {
            list << it->getName() + " earned " + QString::number(it->getSalary()) + "$";
    }
    for(auto it = m_park->getIndependentDrivers().begin(); it != m_park->getIndependentDrivers().end() ; ++it)
    {
            list << it->getName() + " earned " + QString::number(it->getSalary()) + "$";
    }
    m_model->setStringList(list);
    ui->listViewSalary->setModel(m_model);
}

void FinancialWindow::on_buttonPaySalary_clicked()
{
    m_park->paySalaries();
    updateListSalary();
}
