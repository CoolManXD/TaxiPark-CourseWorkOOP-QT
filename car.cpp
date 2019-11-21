#include "car.h"

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
