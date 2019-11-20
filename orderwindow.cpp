#include "orderwindow.h"
#include "ui_orderwindow.h"
#include <QMessageBox>

OrderWindow::OrderWindow(Map *map, TaxiPark *park,QWidget *parent) :
    m_map(map),
    m_park(park),
    QWidget(parent),
    ui(new Ui::OrderWindow)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true);
    for (auto it = m_map->listOfStreets.begin(); it != m_map->listOfStreets.end(); ++it)
    {
        ui->listDestination->addItem(it.key());
        ui->listLocation->addItem(it.key());
    }
}

OrderWindow::~OrderWindow()
{
    delete ui;
}

void OrderWindow::refreshListOfSearch()
{
    ui->editSearchLocation->setText("");
    ui->editSearchDestination->setText("");
    ui->listLocation->clear();
    ui->listDestination->clear();
    for (auto it = m_map->listOfStreets.begin(); it != m_map->listOfStreets.end(); ++it)
    {
        ui->listDestination->addItem(it.key());
        ui->listLocation->addItem(it.key());
    }
}

//----------------------------------------------------------------
void OrderWindow::on_editSearchLocation_textChanged(const QString &str)
{
    ui->listLocation->clear();

    QString selectedStreet;
    if (ui->listDestination->currentItem() != NULL)
        selectedStreet = ui->listDestination->currentItem()->text();
    else
        selectedStreet = "";

    for (auto it = m_map->listOfStreets.begin(); it != m_map->listOfStreets.end(); ++it)
    {
        if (it.key().contains(str, Qt::CaseInsensitive) && it.key() != selectedStreet)
        {
            ui->listLocation->addItem(it.key());
        }
    }
}


//поиск улицы. изменение в строке поиска. destination
void OrderWindow::on_editSearchDestination_textChanged(const QString &str)
{
    ui->listDestination->clear();

    QString selectedStreet; // улица выбранная в другом списке
    if (ui->listLocation->currentItem() != NULL)
        selectedStreet = ui->listLocation->currentItem()->text();
    else
        selectedStreet = "";

    for (auto it = m_map->listOfStreets.begin(); it != m_map->listOfStreets.end(); ++it)
    {
        if (it.key().contains(str, Qt::CaseInsensitive) && it.key() != selectedStreet)
        {
            ui->listDestination->addItem(it.key());
        }
    }
}

//поиск улицы. изменение в строке поиска. location
void OrderWindow::on_listLocation_itemClicked()
{
    QString currentItem = "";
    if(ui->listDestination->currentItem() != NULL)
        currentItem = ui->listDestination->currentItem()->text();

    on_editSearchDestination_textChanged(ui->editSearchDestination->text());

    if(currentItem != "")
    {
        int count = ui->listDestination->count();
        for(int index = 0; index < count; index++)
        {
            QListWidgetItem *item = ui->listDestination->item(index);
            if (item->text() == currentItem)
            {
                ui->listDestination->setCurrentItem(item);
                break;
            }
        }

//        QList<QListWidgetItem *> items =  ui->listDestination->findItems(currentItem, Qt::MatchExactly);
//        if (items.size() != 0)
//            ui->listDestination->setCurrentItem(items[0]);
    }

//    QList<QListWidgetItem *> items =  ui->listD->findItems(item->text(), Qt::MatchExactly);
//    if (items.size() != 0)
//        delete ui->listD->takeItem(ui->listD->row(items[0]));

}

void OrderWindow::on_listDestination_itemClicked()
{
    QString currentItem = "";
    if(ui->listLocation->currentItem() != NULL)
        currentItem = ui->listLocation->currentItem()->text();

    on_editSearchLocation_textChanged(ui->editSearchLocation->text());

    if(currentItem != "")
    {
        int count = ui->listLocation->count();
        for(int index = 0; index < count; index++)
        {
            QListWidgetItem *item = ui->listLocation->item(index);
            if (item->text() == currentItem)
            {
                ui->listLocation->setCurrentItem(item);
                break;
            }
        }

//        QList<QListWidgetItem *> items =  ui->listLocation->findItems(current, Qt::MatchExactly);
//        if (items.size() != 0)
//            ui->listLocation->setCurrentItem(items[0]);
    }
}

//----------------------------------------------------------------
void OrderWindow::on_confirmButton_clicked()
{
    //потом сдлеать меседж бокс
    const QString name = ui->editNameClient->text();
    if(!ui->listLocation->currentIndex().isValid())
    {
        QMessageBox::warning(this, "Not entered data", "Selecet location!");
        return;
    }
    if(!ui->listDestination->currentIndex().isValid())
    {
        QMessageBox::warning(this, "Not entered data", "Select destination!");
        return;
    }
    if(ui->editNameClient->text() == "")
    {
        QMessageBox::warning(this, "Not entered data", "Fill the client's name!");
        return;
    }

    const QString location = ui->listLocation->currentItem()->text();
    const QString destination = ui->listDestination->currentItem()->text();
    bool isVip = ui->checkBoxIsVip->isChecked();
    m_park->receiveOrder(new Client{*m_map, name, location, destination});

    QString way = "";
    float time;
    float price;
    float salary;
    if(!m_park->completeOrder(way, time, price, salary, isVip))
    {
        QMessageBox::information(this, "", "All drivers are busy!");
        return;
    }

    ui->textWay->setText(way);
    ui->valueTimeWay->display(double(time));
    ui->valuePrice->display(double(price));
    ui->valueSalary->display(double(salary));
    QMessageBox::information(this, "", "Order is accepted. Wait for driver.");
    refreshListOfSearch();
}
