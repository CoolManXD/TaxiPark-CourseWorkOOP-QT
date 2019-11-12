#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_park.setDriverMap(new DriverMap{ m_map });
    for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
    {
        ui->listD->addItem(it.key());
        ui->listL->addItem(it.key());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refreshListOfSearch()
{
    ui->editSearchL->setText("");
    ui->editSearchD->setText("");
    ui->listL->clear();
    ui->listD->clear();
    for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
    {
        ui->listD->addItem(it.key());
        ui->listL->addItem(it.key());
    }
}

void MainWindow::on_editSearchL_textChanged(const QString &str)
{
    ui->listL->clear();
    QString subStr = str.toUpper();
    QString street;

    QString selectedStreet;
    if (ui->listD->currentItem() != NULL)
        selectedStreet = ui->listD->currentItem()->text().toUpper();
    else
        selectedStreet = "";

    for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
    {
        street = it.key().toUpper();

        if (street.indexOf(subStr) != -1 && street != selectedStreet)
        {
            ui->listL->addItem(it.key());
        }
    }
}


//поиск улицы. изменение в строке поиска. destinatio
void MainWindow::on_editSearchD_textChanged(const QString &str)
{
    ui->listD->clear();
    QString subStr = str.toUpper(); // подстрока для поиска
    QString street; //

    QString selectedStreet; // улица выбранная в другом списке
    if (ui->listL->currentItem() != NULL)
        selectedStreet = ui->listL->currentItem()->text().toUpper();
    else
        selectedStreet = "";

    for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
    {
        street = it.key().toUpper();
        if (street.indexOf(subStr) != -1 && street != selectedStreet)
        {
            ui->listD->addItem(it.key());
        }
    }
}

//поиск улицы. изменение в строке поиска. location
void MainWindow::on_listL_itemClicked()
{
    QString current = "";
    if(ui->listD->currentItem() != NULL)
        current = ui->listD->currentItem()->text();

    on_editSearchD_textChanged(ui->editSearchD->text());

    if(current != "")
    {
        QList<QListWidgetItem *> items =  ui->listD->findItems(current, Qt::MatchExactly);
        if (items.size() != 0)
            ui->listD->setCurrentItem(items[0]);
    }

//    QList<QListWidgetItem *> items =  ui->listD->findItems(item->text(), Qt::MatchExactly);
//    if (items.size() != 0)
//        delete ui->listD->takeItem(ui->listD->row(items[0]));

}

void MainWindow::on_listD_itemClicked()
{
    QString current = "";
    if(ui->listL->currentItem() != NULL)
        current = ui->listL->currentItem()->text();

    on_editSearchL_textChanged(ui->editSearchL->text());

    if(current != "")
    {
        QList<QListWidgetItem *> items =  ui->listL->findItems(current, Qt::MatchExactly);
        if (items.size() != 0)
            ui->listL->setCurrentItem(items[0]);
    }
}
