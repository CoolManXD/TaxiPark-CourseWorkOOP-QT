#include "infodriverswindow.h"
#include "ui_infodriverswindow.h"

InfoDriversWindow::InfoDriversWindow(TaxiPark *park, QWidget *parent) :
    m_park(park),
    QWidget(parent),
    ui(new Ui::InfoDriversWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);

    m_model_Dependent = new QStringListModel(this);
    m_model_Independent = new QStringListModel(this);
    loadInfoView();
}

InfoDriversWindow::~InfoDriversWindow()
{
    delete ui;
}

void InfoDriversWindow::loadInfoView()
{
    QStringList list_Dependent;
    QStringList list_Independent;

    for(auto it = m_park->getDependentDrivers().begin(); it != m_park->getDependentDrivers().end() ; ++it)
    {
            list_Dependent << it->getName();
    }
    m_model_Dependent->setStringList(list_Dependent);
    ui->listDependentDrivers->setModel(m_model_Dependent);

    for(auto it = m_park->getIndependentDrivers().begin(); it != m_park->getIndependentDrivers().end() ; ++it)
    {
            list_Independent << it->getName();
    }
    m_model_Independent->setStringList(list_Independent);
    ui->listIndependentDrivers->setModel(m_model_Independent);
}

void InfoDriversWindow::on_listDependentDrivers_clicked(const QModelIndex &index)
{
    QString driverName = index.data(Qt::DisplayRole).toString();
    for(auto it = m_park->getDependentDrivers().begin(); it != m_park->getDependentDrivers().end() ; ++it)
    {
            if (driverName == it->getName())
            {
                ui->labelName_Dependent->setText("Full name: " + it->getName());
                ui->labelYearExp_Dependent->setText("Year experience: " + QString::number(it->getYearExp()));
                ui->labelModel_Dependent->setText("Model of the car: " + it->getCar().getModel());
                ui->labelRegPlate_Dependent->setText("Registration plate of the car: " + it->getCar().getRegPlate());
                QString symbol = it->getCar().isVip() ? "+" : "-";
                ui->labelVip_Dependent->setText("Vip car: " + symbol);
                break;
            }
    }
}

void InfoDriversWindow::on_listIndependentDrivers_clicked(const QModelIndex &index)
{
    QString driverName = index.data(Qt::DisplayRole).toString();
    for(auto it = m_park->getIndependentDrivers().begin(); it != m_park->getIndependentDrivers().end() ; ++it)
    {
            if (driverName == it->getName())
            {
                ui->labelName_Independent->setText("Full name: " + it->getName());
                ui->labelYearExp_Independent->setText("Year experience: " + QString::number(it->getYearExp()));
                ui->labelModel_Independent->setText("Model of the car: " + it->getCar().getModel());
                ui->labelRegPlate_Independent->setText("Registration plate of the car: " + it->getCar().getRegPlate());
                QString symbol = it->getCar().isVip() ? "+" : "-";
                ui->labelVip_Independent->setText("Vip car: " + symbol);
                symbol = it->getCar().isVip() ? "+" : "-";
                ui->labelInsurance_Independent->setText("Insurance from the company: " + symbol);
                symbol = it->isInsured() ? "+" : "-";
                ui->labelRepairServ_Independent->setText("Fuel from the company: " + symbol);
                symbol = it->isFuel() ? "+" : "-";
                ui->labelFuel_Independent->setText("Repair services from the company: " + symbol);
                break;
            }
    }
}
