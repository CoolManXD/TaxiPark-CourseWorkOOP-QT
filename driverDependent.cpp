#include "driverDependent.h"
#include "car.h"

//-------------------������� �������-------------------- 
void DriverDependent::setSalary(float salary)
{
	m_salary = salary;
}

float DriverDependent::getSalary()
{
	return m_salary;
}

//-------------------������� ����������� �����-------------------- 
float DriverDependent::getPercentageOfOrder()
{
	return m_percentageOfOrder;
}


//--------------------������� ���������---------------------
void DriverDependent::calculatePrice(float distance,float &price, float &salary)
{
    price = distance;
    salary = price * m_percentageOfOrder;
	m_salary += salary;
}
//-------------------���������� ����������-------------------- 
float operator+(float money, DriverDependent& driver)
{
	return money + driver.getSalary();
}

float operator+(DriverDependent& driver, float money)
{
	return money + driver.getSalary();
}

float operator+=(float money, DriverDependent& driver)
{
	return money + driver.getSalary();
}
