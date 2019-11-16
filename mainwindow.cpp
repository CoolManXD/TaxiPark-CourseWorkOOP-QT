#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "busylistwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_park.setDriverMap(new DriverMap{ m_map });
    for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
    {
        ui->listDestination->addItem(it.key());
        ui->listLocation->addItem(it.key());
    }

//    p = new BusyListWindow();
//    p2 = new QLabel();
//    p2->setText("aaaaaaaaaa");
//    ui->stackedWidget->addWidget(p2);
//    ui->stackedWidget->addWidget(p);

//    ui->comboBox->addItem(tr("Page 1"));
//    ui->comboBox->addItem(tr("Page 2"));
//    ui->comboBox->addItem(tr("Page 3"));
//    ui->comboBox->addItem(tr("Page 4"));
//    connect(ui->comboBox, SIGNAL(activated(int)),ui->stackedWidget,SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshListOfSearch()
{
    ui->editSearchLocation->setText("");
    ui->editSearchDestination->setText("");
    ui->listLocation->clear();
    ui->listDestination->clear();
    for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
    {
        ui->listDestination->addItem(it.key());
        ui->listLocation->addItem(it.key());
    }
}

//----------------------------------------------------------------
void MainWindow::on_editSearchLocation_textChanged(const QString &str)
{
    ui->listLocation->clear();
    QString subStr = str.toUpper();
    QString street;

    QString selectedStreet;
    if (ui->listDestination->currentItem() != NULL)
        selectedStreet = ui->listDestination->currentItem()->text().toUpper();
    else
        selectedStreet = "";

    for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
    {
        street = it.key().toUpper();

        if (street.indexOf(subStr) != -1 && street != selectedStreet)
        {
            ui->listLocation->addItem(it.key());
        }
    }
}


//поиск улицы. изменение в строке поиска. destination
void MainWindow::on_editSearchDestination_textChanged(const QString &str)
{
    ui->listDestination->clear();
    QString subStr = str.toUpper(); // подстрока для поиска
    QString street; //

    QString selectedStreet; // улица выбранная в другом списке
    if (ui->listLocation->currentItem() != NULL)
        selectedStreet = ui->listLocation->currentItem()->text().toUpper();
    else
        selectedStreet = "";

    for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
    {
        street = it.key().toUpper();
        if (street.indexOf(subStr) != -1 && street != selectedStreet)
        {
            ui->listDestination->addItem(it.key());
        }
    }
}

//поиск улицы. изменение в строке поиска. location
void MainWindow::on_listLocation_itemClicked()
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

void MainWindow::on_listDestination_itemClicked()
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
void MainWindow::on_confirmButton_clicked()
{
    //потом сдлеать меседж бокс
    const QString name = ui->editNameClient->text();
    if(!ui->listLocation->currentIndex().isValid())
    {
        ui->textInfo->setText("Select location!");
        return;
    }
    if(!ui->listDestination->currentIndex().isValid())
    {
        ui->textInfo->setText("Select destination!");
        return;
    }
    const QString location = ui->listLocation->currentItem()->text();
    const QString destination = ui->listDestination->currentItem()->text();
    m_park.receiveOrder(new Client{m_map, name, location, destination});
    QString way = "";
    float time;
    float price;
    float salary;
    if(!m_park.completeOrder(way, time, price, salary))
    {
        ui->textInfo->setText("Sorry! All drivers are busy!");
        return;
    }
    ui->textWay->setText(way);
    ui->valueTimeWay->display(double(time));
    ui->valuePrice->display(double(price));
    ui->valueSalary->display(double(salary));
    ui->textInfo->setText("Thank for order. Please wait for driver.");
    refreshListOfSearch();
}

//---------------открыть окно с списком зайнятости водителей-----------------
void MainWindow::on_actionBusyList_triggered()
{
    BusyListWindow *window = new BusyListWindow(this, &m_park);
    this->hide();
    window->show();
}

