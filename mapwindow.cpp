#include "mapwindow.h"
#include "ui_mapwindow.h"

MapWindow::MapWindow(TaxiPark *park, QWidget *parent) :
    m_park(park),
    QWidget(parent),
    ui(new Ui::MapWindow)
{
    ui->setupUi(this);
    m_model = new QStringListModel(this);
    updateWaysView();
}

MapWindow::~MapWindow()
{
    delete ui;
}

 void MapWindow::updateWaysView()
 {
     QStringList list;
     DriverMap *tempMap = Driver::getDriverMap();
     int i = 0;
     for(auto it = tempMap->m_trafficJams.begin(); it != tempMap->m_trafficJams.end() ; ++it)
     {
         for(auto it2 = (*it).begin(); it2 != (*it).end(); ++it2)
         {
             list << tempMap->m_map.listOfStreets.key(i) + " (S" + QString::number(i+1) + ") -> " + tempMap->m_map.listOfStreets.key(it2->first) + " (S" + QString::number(it2->first + 1) + ") = " + QString::number(it2->second);
         }
         i++;
     }
     m_model->setStringList(list);
     ui->listWaysView->setModel(m_model);
 }
