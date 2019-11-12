#include "driverMap.h"
#include "map.h"
#include <cstdlib>
#include <ctime>

//-------------------Конструктор создание карты водителя-------------------- 
DriverMap::DriverMap(Map& map) : m_map(map)
{
	m_trafficJams.resize(m_map.quantityStreet);
	for (int i = 0; i < m_map.quantityStreet; i++)
	{
        for (auto it = m_map.mapOfTown[i].begin(); it != m_map.mapOfTown[i].end(); ++it)
        {
            m_trafficJams[i].append(qMakePair(it->first, 0));
        }
	}
	updateDataTrafficJams();
}

//-------------------Обновление данных о пробках-------------------- 
void DriverMap::updateDataTrafficJams() {
	srand(time(NULL));
    for(auto it = m_trafficJams.begin(); it != m_trafficJams.end(); ++it)
    {
        for(auto it2 = (*it).begin(); it2 != (*it).end(); ++it2)
        {
            it2->second = (float(rand() % 5 + 1) / 2) * it2->second;
            /*m_trafficJams[i][j].second = m_map.mapOfTown[i][j].second;*/
        }
    }
}

