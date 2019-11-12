#pragma once
#include <QtCore>

class TaxiService
{
public:
    TaxiService() {}

    virtual float findWay(const QString&, const QString&) = 0;
    virtual void calculatePrice(float) = 0;

    virtual const QString& getLocation() = 0;
    virtual void setLocation(const QString&) = 0;

	virtual void changeIsBusy() = 0;
    virtual void setTimeAttributes(float) = 0;
	
    virtual ~TaxiService() {}
};

