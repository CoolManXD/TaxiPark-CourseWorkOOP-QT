#include "driverIndependent.h"
#include "car.h"

//-------------------Функции доступа-------------------- 
void DriverIndependent::setSalary(float salary)
{
	m_salary = salary;
}

float DriverIndependent::getSalary()
{
	return m_salary;
}

bool DriverIndependent::isInsured()
{
	return m_isCompanyInsured;
}
bool DriverIndependent::isRepairServ()
{
	return m_isCompanyRepairServ;
}
bool DriverIndependent::isFuel()
{
	return m_isCompanyFuel;
}

//-------------------Геттеры статический полей-------------------- 
float DriverIndependent::getPercentageOfOrder()
{
	return m_percentageOfOrder;
}

float DriverIndependent::getPercentageOfInsured()
{
	return m_percentageOfInsured;
}

float DriverIndependent::getPercentageOfRepairServ()
{
	return m_percentageOfRepairServ;
}

float DriverIndependent::getPercentageOfFuel()
{
	return m_percentageOfFuel;
}

//--------------------Услуги такси---------------------------

void DriverIndependent::calculatePrice(float distance,float &price, float &salary)
{
	float percentage = m_percentageOfOrder;
	if (m_isCompanyInsured) percentage -= m_percentageOfInsured;
	if (m_isCompanyRepairServ) percentage -= m_percentageOfRepairServ;
	if (m_isCompanyFuel) percentage -= m_percentageOfFuel;
    price = distance;
    salary = distance * m_percentageOfOrder;
	m_salary += salary;
}

//-------------------Перегрузки операторов-------------------- 
float operator+(float money, DriverIndependent& driver)
{
	return money + driver.getSalary();
}

float operator+(DriverIndependent& driver, float money)
{
	return money + driver.getSalary();
}

float operator+=(float money, DriverIndependent& driver)
{
	return money + driver.getSalary();
}
