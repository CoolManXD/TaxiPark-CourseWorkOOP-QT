#pragma once

#include <QtCore>
class Map;

class DriverMap
{
private:
	/*int quantityStreet;*/
	
public:
	Map& m_map;
    QVector<QVector<QPair<int, float>>> m_trafficJams;
	DriverMap(Map&);
	void updateDataTrafficJams();
};
