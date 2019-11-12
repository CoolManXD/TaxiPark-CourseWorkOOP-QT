#pragma once
#include <QtCore>

//#include "driverMap.h"
//#include "client.h"
//class DriverMap;
//class Client;

class Map {
private:
	void loadMap();
public:
    int quantityStreet;
    QMap<QString, int> listOfStreets;
    QVector<QVector<QPair<int, float>>> mapOfTown;
    Map()
    {
		loadMap();
	}
    /*friend class DriverMap;
	friend class Client;*/
	/*friend DriverMap::DriverMap(const Map& map);*/
	/*friend void DriverMap::updateDataTrafficJams();*/
};
