#include "taxiPark.h"
#include "client.h"
#include <QMessageBox>
#include <iostream>

//-------------------Загрузка данных с файла и проверка-------------------- 

void TaxiPark::loadData() {
    QFile fsCar(":/data/dataBase/carsDependent.txt");
    QFile fsDriver(":/data/dataBase/driversDependent.txt");
    if (!fsCar.open(QFile::ReadOnly | QFile::Text) || !fsDriver.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream inCar(&fsCar);
    QTextStream inDriver(&fsDriver);

    QString name;
	int yearExp;
    QString model;
    QString regPlate;
    QChar symbol;
	bool isVip;
    while (!inCar.atEnd())
	{
        inCar >> model;
        if (inCar.atEnd()) break;
        inCar >> regPlate;
        inCar >> symbol;
        inCar >> symbol;
        inDriver >> name;
        int pos = name.indexOf('_');
        if(pos != -1)
            name[pos] = ' ';
        inDriver >> yearExp;
		isVip = (symbol == '+') ? true : false;
        driversDependent.append(DriverDependent(name, yearExp, Car(model, regPlate, isVip)));
	}
	fsCar.close();
	fsDriver.close();

    fsCar.setFileName(":/data/dataBase/carsIndependent.txt");
    fsDriver.setFileName(":/data/dataBase/driversIndependent.txt");
    if (!fsCar.open(QFile::ReadOnly | QFile::Text) || !fsDriver.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    inCar.setDevice(&fsCar);
    inDriver.setDevice(&fsDriver);

	bool isInsured;
	bool isRepairServ;
	bool isFuel;
    QChar symbol1;
    QChar symbol2;
    QChar symbol3;
    while (!inCar.atEnd())
	{
        inCar >> model;
        if (inCar.atEnd()) break;
        inCar >> regPlate;
        inCar >> symbol;
        inCar >> symbol;
        inDriver >> name;
        int pos = name.indexOf('_');
        if(pos != -1)
            name[pos] = ' ';
        inDriver >> yearExp;
        inDriver >> symbol1;
        inDriver >> symbol1;
        inDriver >> symbol2;
        inDriver >> symbol2;
        inDriver >> symbol3;
        inDriver >> symbol3;
		isVip = (symbol == '+') ? true : false;
		isInsured = (symbol1 == '+') ? true : false;
		isRepairServ = (symbol2 == '+') ? true : false;
		isFuel = (symbol3 == '+') ? true : false;
        driversIndependent.append(DriverIndependent(isInsured, isRepairServ, isFuel, name, yearExp, Car(model, regPlate, isVip)));
	}
    fsCar.close();
    fsDriver.close();
}

void TaxiPark::setDriverMap(DriverMap* map)
{
	driversDependent[0].setDriverMap(map);
}

//----------------Получение и выполнение заказа------------------

void TaxiPark::receiveOrder(Client* client)
{
    m_client = client;
}

bool TaxiPark::completeOrder(QString &way, float &time, float &price, float &salary, bool isVip)
{
    busyDriverUpdates();
    float durationToClient = 999999;
    TaxiService* driver = findNearestDriver(durationToClient, isVip);
    if (driver == NULL) return false;
    /*DriverDependent* driver2 = dynamic_cast<DriverDependent*>(driver);*/

    float durationToDesination = driver->findWay(m_client->getLocation(), m_client->getDestination(), way);
    time = durationToClient + durationToDesination;
    driver->setTimeAttributes(time);

//	std::cout << "All trip will take " <<  time << " minutes\n";
    driver->calculatePrice(durationToDesination, price, salary);
    m_earnMoney += price;
    driver->setLocation(m_client->getDestination());
    delete m_client;
    m_client = NULL;
    return true;
}

TaxiService* TaxiPark::findNearestDriver(float& duration, bool isVip)
{
	TaxiService* driver = NULL;
    if (isVip)
    {
        float anotherDuration;
        for (auto it = driversDependent.begin(); it != driversDependent.end(); ++it)
        {
            if (!it->isBusy() && it->getCar().isVip())
            {
                anotherDuration = it->findWay(it->getLocation(), m_client->getLocation());

                if (duration > anotherDuration)
                {
                    duration = anotherDuration;
                    driver = &(*it);
                }
            }
        }

        for (auto it = driversIndependent.begin(); it != driversIndependent.end(); ++it)
        {
            if (!it->isBusy() && it->getCar().isVip())
            {
                anotherDuration = it->findWay(it->getLocation(), m_client->getLocation());

                if (duration > anotherDuration)
                {
                    duration = anotherDuration;
                    driver = &(*it);
                }
            }
        }
        if (driver != NULL)
        {
            driver->changeIsBusy();
            return driver;
        }
        else
        {
            QMessageBox::StandardButton reply = QMessageBox::question(NULL,"Vip","Free VIP car isn't found. Should we find not VIP car?",QMessageBox::Yes | QMessageBox::No);
            if (reply == QMessageBox::No)
            {
                delete m_client;
                m_client = NULL;
                return NULL;
            }
        }
    }

    float anotherDuration;
    for (auto it = driversDependent.begin(); it != driversDependent.end(); ++it)
    {
        if (!it->isBusy())
        {
            anotherDuration = it->findWay(it->getLocation(), m_client->getLocation());

            if (duration > anotherDuration)
            {
                duration = anotherDuration;
                driver = &(*it);
            }
        }
    }

    for (auto it = driversIndependent.begin(); it != driversIndependent.end(); ++it)
    {
        if (!it->isBusy())
        {
            anotherDuration = it->findWay(it->getLocation(), m_client->getLocation());

            if (duration > anotherDuration)
            {
                duration = anotherDuration;
                driver = &(*it);
            }
        }
    }

	if (driver == NULL)
	{
//		std::cout << "Sorry. No free cars :(\n";
		delete m_client;
		m_client = NULL;
		return NULL;
	}

	driver->changeIsBusy();
	return driver;
}

void TaxiPark::busyDriverUpdates()
{
	std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();
	for (auto it = driversDependent.begin(); it != driversDependent.end(); ++it)
	{
		if (it->isBusy())
		{
			if (std::chrono::duration_cast<std::chrono::seconds>(endTime - it->getStartTime()).count() >= it->getBusyTime())
			{
				it->changeIsBusy();
			}
		}
	}

	for (auto it = driversIndependent.begin(); it != driversIndependent.end(); ++it)
	{
		if (it->isBusy())
		{

			if (std::chrono::duration_cast<std::chrono::seconds>(endTime - it->getStartTime()).count() >= it->getBusyTime())
			{
				it->changeIsBusy();
			}
		}
	}
}


void TaxiPark::showListBusyDriver()
{
	busyDriverUpdates();
	std::cout << "List of busy drivers:" << std::endl;
	for (auto it = driversDependent.begin(); it != driversDependent.end(); ++it)
	{
		if (it->isBusy())
		{
            //std::cout << it->getName() << std::endl;
		}
	}

	for (auto it = driversIndependent.begin(); it != driversIndependent.end(); ++it)
	{
		if (it->isBusy())
		{
            //std::cout << it->getName() << std::endl;
		}
	}
}

void TaxiPark::showListNoBusyDriver()
{
	busyDriverUpdates();
	std::cout << "List of no busy drivers:" << std::endl;
	for (auto it = driversDependent.begin(); it != driversDependent.end(); ++it)
	{
		if (!(it->isBusy()))
		{
            //std::cout << it->getName() << std::endl;
		}
	}

	for (auto it = driversIndependent.begin(); it != driversIndependent.end(); ++it)
	{
		if (!(it->isBusy()))
		{
            //std::cout << it->getName() << std::endl;
		}
	}
}


//----------------Получение конкретного водителя------------------
DriverDependent& TaxiPark::getDependent(const int index)
{
	return driversDependent[index];
}
DriverIndependent& TaxiPark::getIndependent(const int index)
{
	return driversIndependent[index];
}


//----------------Выплата зарплаты------------------
void TaxiPark::paySalaries()
{
	float totalSalary{ 0 };
	for (auto it = driversDependent.begin(); it != driversDependent.end(); ++it)
	{
		totalSalary = totalSalary + (*it);
		it->setSalary(0);
	}
	for (auto it = driversIndependent.begin(); it != driversIndependent.end(); ++it)
	{
		totalSalary = totalSalary + (*it);
		it->setSalary(0);
	}
	m_earnMoney -= totalSalary;
	std::cout << "Net profit: " << m_earnMoney << std::endl;
	std::cout << "Driver received in total: " << totalSalary << std::endl;
}

//-------------------Добавление в базу новых водителей-------------------- 
void TaxiPark::addDependentDriver()
{
	std::cout << "\nFill profile (dependent driver) \n\n";
	DriverDependent driver;
	std::cin >> driver;
	driversDependent.push_back(driver);
}

void TaxiPark::addIndependentDriver()
{
	std::cout << "Fill profile (independent driver) \n\n";
	DriverIndependent driver;
	std::cin >> driver;
	driversIndependent.push_back(driver);
}

//-------------------Перегрузки операторов-------------------- 
std::ostream& operator<< (std::ostream& out, TaxiPark& park)
{
	int i = 1;
	out << "Dependent drivers\n";
	for (auto it = park.driversDependent.begin(); it != park.driversDependent.end(); ++it)
	{
		out << "\n" << i++ << ")\n" << *it;
	}
	i = 1;
	out << "\nIndependent drivers\n";
	for (auto it = park.driversIndependent.begin(); it != park.driversIndependent.end(); ++it)
	{
		out << "\n" << i++ << ")\n" << *it;
	}
	return out;
}
