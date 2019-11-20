#include "map.h"
#include <QDir>

//-------------------Загрузка карты(графа) с файла-------------------- 
void Map::loadMap()
{
    QDir dir(QDir::currentPath());
//    QFile fs(":/data/dataBase/listOfStreets.txt");
    QFile fs(dir.absoluteFilePath("dataBase/listOfStreets.txt"));
    if (!fs.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream in(&fs);

    QString street;
	int index;
    while (!in.atEnd())
	{
        in >> street;
        int pos = street.indexOf('_');
        if(pos != -1)
            street[pos] = ' ';
        in >> index;
        listOfStreets.insert(street, index);
	}

	fs.close();

//    fs.setFileName(":/data/dataBase/map.txt");
    fs.setFileName(dir.absoluteFilePath("dataBase/map.txt"));
    if (!fs.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    in.setDevice(&fs);

    QString from, to;
	float duration;
    in >> quantityStreet;
	mapOfTown.resize(quantityStreet);
    while (!in.atEnd())
	{
        in >> from;
        int pos = from.indexOf('_');
        if(pos != -1)
            from[pos] = ' ';
        in >> to;
        pos = to.indexOf('_');
        if(pos != -1)
            to[pos] = ' ';
        in >> duration;
		/*map[from[0] - 49].push_back(std::pair<std::string, int>(to, duration)); // код Аски '0' = 48
		map[to[0] - 49].push_back(std::pair<std::string, int>(from, duration));*/
        mapOfTown[listOfStreets[from]].append(qMakePair(listOfStreets[to], duration));
        mapOfTown[listOfStreets[to]].append(qMakePair(listOfStreets[from], duration));
	}
	fs.close();
}
