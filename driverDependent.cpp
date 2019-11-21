#include "driverDependent.h"
#include "car.h"

//-------------------Функции доступа-------------------- 
void DriverDependent::setSalary(float salary)
{
	m_salary = salary;
}

float DriverDependent::getSalary()
{
	return m_salary;
}

//-------------------Геттеры статический полей-------------------- 
float DriverDependent::getPercentageOfOrder()
{
	return m_percentageOfOrder;
}


//--------------------Подсчет стоимости---------------------
void DriverDependent::calculatePrice(float distance,float &price, float &salary)
{
    price = distance;
    salary = price * m_percentageOfOrder;
	m_salary += salary;
}
//-------------------Перегрузка операторов-------------------- 
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
