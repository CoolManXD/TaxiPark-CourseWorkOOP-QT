#include "client.h"
#include "map.h"

//-------------------Конструктор оформления клиента-------------------- 
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
