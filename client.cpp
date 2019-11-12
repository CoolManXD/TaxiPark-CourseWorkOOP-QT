#include "client.h"
#include "map.h"
#include <iostream>

//-------------------Конструктор оформления клиента-------------------- 
Client::Client(const Map& map) : m_map{ map }
{
	std::cout << "Fill profile\n";
	std::cout << "Name: ";
    //std::getline(std::cin, m_name);

	std::cout << std::endl << "List of streets\n";
	for (auto it = m_map.listOfStreets.begin(); it != m_map.listOfStreets.end(); ++it)
	{
        //std::cout << it->first << std::endl;
	}
	std::cout << std::endl << "Fill your location\n";
	do
	{
		std::cout << "Location: ";
    //	std::getline(std::cin, m_location);
	} while (m_map.listOfStreets.find(m_location) == m_map.listOfStreets.end());
	std::cout << std::endl << "Fill your destination\n";
	do
	{
		std::cout << "Destination: ";
        //std::getline(std::cin, m_destination);
	} while (m_map.listOfStreets.find(m_destination) == m_map.listOfStreets.end() || m_destination == m_location);

}

Client::Client(const Map& map, QString name, QString location, QString destination)
	: m_map{ map }, m_name{ name }, m_location{ location }, m_destination{ destination }
{

}

//-------------------Функции доступа-------------------- 
const QString& Client::getLocation()
{
	return m_location;
}
const QString& Client::getDestination()
{
	return m_destination;
}
