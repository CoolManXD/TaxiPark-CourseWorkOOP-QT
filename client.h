#pragma once

#include <QString>
class Map;

class Client
{
private:
	const Map& m_map;
    const QString m_name;
    const QString m_location;
    const QString m_destination;
public:
    Client(const Map& map, const QString name, const QString location, const QString destination);
    const QString& getLocation();
    const QString& getDestination();
	~Client(){}
};
