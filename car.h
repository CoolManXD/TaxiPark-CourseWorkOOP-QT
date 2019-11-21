#pragma once
#include <QString>

class DriverDependent;
class DriverIndependent;

class Car {
private:
    QString m_model;
    QString m_regPlate;
	bool m_isVip;
public:
    Car(QString model = "undefined", QString regPlate = "undefined", bool isVip = false)
		: m_model{ model }, m_regPlate{ regPlate }, m_isVip{ isVip }
	{
	}
	Car(const Car &cpyCar)
		: m_model{ cpyCar.m_model }, m_regPlate{ cpyCar.m_regPlate }, m_isVip{ cpyCar.m_isVip }
	{
	}
	
    void setAttributesCar(QString model, QString regPlate, bool isInsured);
    const QString& getModel();
    const QString& getRegPlate();
	bool isVip();
	~Car() {}
};
