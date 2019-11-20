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

    //заполнения списков location и destination
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

//---------очистить поисковые строки и unselect элементы в списках
void OrderWindow::refreshListOfSearch()
{
    ui->editSearchLocation->setText("");
    ui->editSearchDestination->setText("");
    ui->listLocation->clear();
    ui->listDestination->clear();
    for (auto it = m_map->listOfStreets.begin(); it != m_map->listOfStreets.end(); ++it)
    {
        //ключ QMap - название улицы, значение - уникальный индекс улицы
        ui->listDestination->addItem(it.key());
        ui->listLocation->addItem(it.key());
    }
}

//----------поиск location в списке при вводе даных в поисковую строку
void OrderWindow::on_editSearchLocation_textChanged(const QString &str)
{
    ui->listLocation->clear(); //очищение списка location

    QString selectedStreet;
    if (ui->listDestination->currentItem() != NULL) //проверка или выбран элемент в списке destination, true - запомнить, false - пустая строка
        selectedStreet = ui->listDestination->currentItem()->text();
    else
        selectedStreet = "";

    //поиск улицы, что содержит введеную строку str
    for (auto it = m_map->listOfStreets.begin(); it != m_map->listOfStreets.end(); ++it)
    {
        //если улица не содержит подстроку и не выбранная в списке destination, то добавить ее в списко location
        if (it.key().contains(str, Qt::CaseInsensitive) && it.key() != selectedStreet)
        {
            ui->listLocation->addItem(it.key());
        }
    }
}
//----------поиск destination в списке при вводе даных в поисковую строку
void OrderWindow::on_editSearchDestination_textChanged(const QString &str)
{
    ui->listDestination->clear(); //очищение списка destination

    QString selectedStreet;
    if (ui->listLocation->currentItem() != NULL) //проверка или выбран элемент в списке location, true - запомнить, false - пустая строка
        selectedStreet = ui->listLocation->currentItem()->text();
    else
        selectedStreet = "";

    //поиск улицы, что содержит введеную строку str
    for (auto it = m_map->listOfStreets.begin(); it != m_map->listOfStreets.end(); ++it)
    {
        //если улица не содержит подстроку и не выбранная в списке location, то добавить ее в списко destination
        if (it.key().contains(str, Qt::CaseInsensitive) && it.key() != selectedStreet)
        {
            ui->listDestination->addItem(it.key());
        }
    }
}

//------удаление элемента выбранного в списке location из destination
void OrderWindow::on_listLocation_itemClicked()
{
    QString currentItem = "";
    if(ui->listDestination->currentItem() != NULL) //если в списке destination есть выбранный элемент - запомнить его
        currentItem = ui->listDestination->currentItem()->text();

    on_editSearchDestination_textChanged(ui->editSearchDestination->text()); //обновить список destination уже без выбарнного элемента в location

    if(currentItem != "") //если в списка destination был уже выбран элемент - выбрать его снова
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
//------удаление элемента выбранного в списке destination из location
void OrderWindow::on_listDestination_itemClicked()
{
    QString currentItem = "";
    if(ui->listLocation->currentItem() != NULL) //если в списке location есть выбранный элемент - запомнить его
        currentItem = ui->listLocation->currentItem()->text();

    on_editSearchLocation_textChanged(ui->editSearchLocation->text()); //обновить список location уже без выбарнного элемента в destination

    if(currentItem != "") //если в списка location был уже выбран элемент - выбрать его снова
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
    }
}

//--------обработка и выполение заказа
void OrderWindow::on_confirmButton_clicked()
{
    //присвоение переменным данных формы
    //если что-то не заполненное, то вывести соотвестующие сообщение и отменить обработку
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
    m_park->receiveOrder(new Client{*m_map, name, location, destination}); //передать клиента таксопарку

    QString way = ""; //маршрут
    float time; //время поездки
    float price; //цена поездки
    float salary;// з/п водителя за поездку

    //выполнение заказа. если заказ не может быть выполнен, то вывести соотвествующие сообщение
    if(!m_park->completeOrder(way, time, price, salary, isVip))
    {
        QMessageBox::information(this, "", "All drivers are busy!");
        return;
    }

    //данные поздки передать элементам ui
    ui->textWay->setText(way);
    ui->valueTimeWay->display(double(time));
    ui->valuePrice->display(double(price));
    ui->valueSalary->display(double(salary));
    QMessageBox::information(this, "", "Order is accepted. Wait for driver.");
    refreshListOfSearch();
}
