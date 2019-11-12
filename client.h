#pragma once

#include <QString>
class Map;

class Client
{
private:
	const Map& m_map;
    QString m_name;
    QString m_location;
    QString m_destination;
public:
	Client(const Map& map);
    Client(const Map& map, QString name, QString location, QString destination);
    const QString& getLocation();
    const QString& getDestination();
	~Client(){}
};
