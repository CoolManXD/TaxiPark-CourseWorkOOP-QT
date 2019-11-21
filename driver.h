#pragma once

//#include <QtCore>
#include <chrono>
#include "taxiService.h"
#include "car.h"

class DriverMap;

class Driver: public TaxiService {
private:
    QString m_name;
	int m_yearExp;
	Car m_car;

	bool m_isBusy{ false };
    float m_busyTime{ 0 };
	std::chrono::steady_clock::time_point m_startTime;

    QString m_location{ "Steinway Street" };
	static DriverMap* m_driverMap;

public:
    Driver(QString name = "undefined", int yearExp = 0, const Car& car = Car("undefined", "undefined", false))
		:m_name{ name }, m_yearExp{ yearExp }, m_car{ car }
	{

	}
    const QString& getName();
	int getYearExp();
	Car& getCar();

	bool isBusy();
	double getBusyTime();
	std::chrono::steady_clock::time_point& getStartTime();

	static void setDriverMap(DriverMap*);
	static DriverMap* getDriverMap();

	virtual void changeIsBusy() override final;
    virtual void setTimeAttributes(float) override final;

    virtual const QString& getLocation() override final;
    virtual void setLocation(const QString&) override final;

    virtual float findWay(const QString&, const QString&) override final;
    virtual float findWay(const QString& , const QString& , QString &) override final; //возвращает маршрут

    virtual void calculatePrice(float, float &, float &) override {}
    virtual ~Driver() override {}
};
