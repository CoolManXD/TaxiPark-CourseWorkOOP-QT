#include "taxiPark.h"
#include "driverMap.h"
#include "client.h"
#include <QMessageBox>

#include <iostream>

//-------------------�������� ������ � ����� � ��������-------------------- 

void TaxiPark::loadData() {
    QDir dir(QDir::currentPath()); //���������� ���� � ������������ �����

    QFile fsCar(dir.absoluteFilePath("dataBase/carsDependent.txt")); //���������� ��������� ���������
    QFile fsDriver(dir.absoluteFilePath("dataBase/driversDependent.txt")); //���� � ��������� ���������
    QFile fsSalary(dir.absoluteFilePath("dataBase/salaryDependent.txt")); //���� � ��������� ���������

    if (!fsCar.open(QFile::ReadOnly | QFile::Text) || !fsDriver.open(QFile::ReadOnly | QFile::Text) || !fsSalary.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    QTextStream inCar(&fsCar);
    QTextStream inDriver(&fsDriver);
    QTextStream inSalary(&fsSalary);

    float salary; //�/�
    QString name; //��� ��������
    int yearExp; //���� ��������
    QString model; //������ ����������
    QString regPlate; //������������� ������
    QChar symbol; //������ vip (+/-)
	bool isVip;
    while (!inCar.atEnd())
	{
        inCar >> model;
        if (inCar.atEnd()) break;
        inCar >> regPlate;
        inCar >> symbol;
        inCar >> symbol;
        inSalary >> salary;
        inDriver >> name;
        int pos = name.indexOf('_'); //������ '_' ������ ��������� � ������
        if(pos != -1)
            name[pos] = ' ';
        inDriver >> yearExp;
		isVip = (symbol == '+') ? true : false;
        driversDependent.append(DriverDependent(salary, name, yearExp, Car(model, regPlate, isVip)));
	}
	fsCar.close();
	fsDriver.close();
    fsSalary.close();

    fsCar.setFileName(dir.absoluteFilePath("dataBase/carsIndependent.txt"));//���������� ����������� ���������
    fsDriver.setFileName(dir.absoluteFilePath("dataBase/driversIndependent.txt")); //���� � ����������� ���������
    fsSalary.setFileName(dir.absoluteFilePath("dataBase/salaryIndependent.txt"));

    if (!fsCar.open(QFile::ReadOnly | QFile::Text) || !fsDriver.open(QFile::ReadOnly | QFile::Text) || !fsSalary.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    inCar.setDevice(&fsCar);
    inDriver.setDevice(&fsDriver);
    inSalary.setDevice(&fsSalary);

    bool isInsured; //��� ���������� ��������� ��������
    bool isRepairServ; //��� ���������� ��������� ������ ��������
    bool isFuel; //��� ���������� ������ ��������
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
        inSalary >> salary;
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
        driversIndependent.append(DriverIndependent(salary, isInsured, isRepairServ, isFuel, name, yearExp, Car(model, regPlate, isVip)));
	}
    fsCar.close();
    fsDriver.close();
    fsSalary.close();

    fsSalary.setFileName(dir.absoluteFilePath("dataBase/companyInfo.txt"));
    if (!fsSalary.open(QFile::ReadOnly | QFile::Text))
    {
        return;
    }
    inSalary.setDevice(&fsSalary);
    inSalary >> m_earnMoney;
    fsSalary.close();
}

//�������� ��������� ����� (static)
void TaxiPark::setDriverMap(DriverMap* map)
{
    //driversDependent[0].setDriverMap(map);
    Driver::setDriverMap(map);
}

//----------------��������� � ���������� ������------------------
void TaxiPark::receiveOrder(Client* client)
{
    m_client = client;
}

bool TaxiPark::completeOrder(QString &way, float &time, float &price, float &salary, bool isVip)
{
    busyDriverUpdates(); //���������� ������� ���������� ���������
    Driver::getDriverMap()->updateDataTrafficJams();
    float durationToClient = 999999; // ����� ������� �� �������
    TaxiService* driver = findNearestDriver(durationToClient, isVip); // ����� ���������� ���������� �������� �� �������

    if (driver == NULL) return false; //���� �� ������ ��������� ��������, �� ��������� ��������� ������
    /*DriverDependent* driver2 = dynamic_cast<DriverDependent*>(driver);*/

    //����� ����������� ���� �� ������� � ����� ����������, ����������� ������� ������ � ��������
    float durationToDesination = driver->findWay(m_client->getLocation(), m_client->getDestination(), way);
    time = durationToClient + durationToDesination; // ����� ���� �������
    driver->setTimeAttributes(time); //������ �������� ����� ��������� ���������

    driver->calculatePrice(durationToDesination, price, salary); // ������� ���� ������ � �/�
    m_earnMoney += price; // ��������� � �������� �������� ���� ������
    driver->setLocation(m_client->getDestination()); // ������ �������� ����� �������
    delete m_client;
    m_client = NULL;
    return true;
}

//���������� ������� ���������� ���������
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

//----------------��������� ����������� ��������------------------
DriverDependent& TaxiPark::getDependent(const int index)
{
	return driversDependent[index];
}
DriverIndependent& TaxiPark::getIndependent(const int index)
{
	return driversIndependent[index];
}
QVector<DriverDependent>& TaxiPark::getDependentDrivers()
{
    return driversDependent;
}
QVector<DriverIndependent>& TaxiPark::getIndependentDrivers()
{
    return driversIndependent;
}
float TaxiPark::getCompanyMoney()
{
    return m_earnMoney;
}

//----------------������� ��������------------------
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
    QString message = "Net profit: " + QString::number(m_earnMoney) + "\nTotal size of salary: " + QString::number(totalSalary);
    QMessageBox::information(NULL, "Finance", message);
}

void TaxiPark::saveFinancialInfo()
{
    QDir dir(QDir::currentPath());

    QFile fp(dir.absoluteFilePath("dataBase/companyInfo.txt"));
    if (!fp.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    QTextStream out(&fp);
    out << m_earnMoney;
    fp.close();

    fp.setFileName(dir.absoluteFilePath("dataBase/salaryDependent.txt"));
    if (!fp.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    out.setDevice(&fp);

    for (auto *it = driversDependent.begin(); it != driversDependent.end(); ++it)
        out << it->getSalary() << "\n";
    fp.close();

    fp.setFileName(dir.absoluteFilePath("dataBase/salaryIndependent.txt"));
    if (!fp.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    out.setDevice(&fp);

    for (auto *it = driversIndependent.begin(); it != driversIndependent.end(); ++it)
        out << it->getSalary() << "\n";
    fp.close();
}

//-------------------���������� � ���� ����� ���������-------------------- 
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

//-------------------���������� ����������-------------------- 
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
