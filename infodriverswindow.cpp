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
                ui->labelName_Dependent->setText(it->getName());
                ui->labelYearExp_Dependent->setNum(it->getYearExp());
                ui->labelModel_Dependent->setText(it->getCar().getModel());
                ui->labelRegPlate_Dependent->setText(it->getCar().getRegPlate());
                ui->labelVip_Dependent->setText(it->getCar().isVip() ? "+" : "-");
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
                ui->labelName_Independent->setText(it->getName());
                ui->labelYearExp_Independent->setNum(it->getYearExp());
                ui->labelModel_Independent->setText(it->getCar().getModel());
                ui->labelRegPlate_Independent->setText(it->getCar().getRegPlate());
                ui->labelVip_Independent->setText(it->getCar().isVip() ? "+" : "-");
                ui->labelInsurance_Independent->setText(it->isInsured() ? "+" : "-");
                ui->labelRepairServ_Independent->setText(it->isRepairServ() ? "+" : "-");
                ui->labelFuel_Independent->setText(it->isFuel() ? "+" : "-");
                break;
            }
    }
}
