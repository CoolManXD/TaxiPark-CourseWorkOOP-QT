#pragma once

#include "driver.h"

class DriverIndependent: public Driver {
private:
    float m_salary;
	bool m_isCompanyInsured;
	bool m_isCompanyRepairServ;
	bool m_isCompanyFuel;
	static constexpr float m_percentageOfOrder = 0.9f;
	static constexpr float m_percentageOfInsured = 0.25f;
	static constexpr float m_percentageOfRepairServ = 0.1f;
	static constexpr float m_percentageOfFuel = 0.05f;
public:
	
    DriverIndependent(float salary = 0, bool isCompanyInsured = false, bool isCompanyRepairServ = false, bool isCompanyFuel = false, QString name = "undefined", int yearExp = 0, const Car& car = Car("undefined", "undefined", false))
        :m_salary{salary}, m_isCompanyInsured{ isCompanyInsured }, m_isCompanyRepairServ{ isCompanyRepairServ }, m_isCompanyFuel{ isCompanyFuel }, Driver{ name, yearExp, car }
	{
	}
	void setSalary(float);
	float getSalary();
	bool isInsured();
	bool isRepairServ();
	bool isFuel();
	static float getPercentageOfOrder();
	static float getPercentageOfInsured();
	static float getPercentageOfRepairServ();
	static float getPercentageOfFuel();
    virtual void calculatePrice(float, float&, float&) override final;
    virtual ~DriverIndependent() override {}
	friend std::istream& operator>> (std::istream& in, DriverIndependent&);
};

std::ostream& operator<< (std::ostream&, DriverIndependent&);
float operator+(float money, DriverIndependent& driver);
float operator+(DriverIndependent& driver, float money);
float operator+=(float money, DriverIndependent& driver);
