#include "car.h"
#include <iostream>

//-------------------Функции доступа-------------------- 
void Car::setAttributesCar(QString model, QString regPlate, bool isVip)
{
	m_model = model;
	m_regPlate = regPlate;
	m_isVip = isVip;
}

const QString& Car::getModel()
{
	return m_model;
}
const QString& Car::getRegPlate()
{
	return m_regPlate;
}
bool Car::isVip()
{
	return m_isVip;
}

//-------------------Перегрузка операторов-------------------- 
std::ostream& operator<< (std::ostream& out, Car& car)
{
    //out << "Model: " << car.getModel() << "\nRegistation Plate: " << car.getRegPlate() << "\nVip: ";
	if (car.isVip()) out << "+\n";
	else out << "-\n";
	return out;
}

std::istream& operator>> (std::istream& in, Car& car)
{
	std::cout << "Model: ";
    //in >> car.m_model;
	std::cout << "Registation plate: ";
    //in >> car.m_regPlate;
	std::cout << "Is VIP (+/-): ";
	char choosen;
	std::cin >> choosen;
	if (choosen == '+') car.m_isVip = true;
	else car.m_isVip = false;
	return in;
}
