#pragma once
//#include <QtCore>
#include "driverDependent.h"
#include "driverIndependent.h"

class BusyListWindow;

class Client;

class TaxiPark {
private:
    QVector<DriverDependent> driversDependent;
    QVector<DriverIndependent> driversIndependent;
	Client* m_client{ NULL };
	float m_earnMoney{ 10000 };
	void loadData();
public:
	TaxiPark() {
		loadData();
	}
	bool checkLoadData();

	void receiveOrder(Client*);
    bool completeOrder(QString &, float &, float &, float &);
    TaxiService* findNearestDriver(float&);
	void busyDriverUpdates();

	void showListBusyDriver();
	void showListNoBusyDriver();
    DriverDependent& getDependent(const int);
    DriverIndependent& getIndependent(const int);

	void paySalaries();

	void addDependentDriver();
	void addIndependentDriver();

	void setDriverMap(DriverMap*);

	friend std::ostream& operator<< (std::ostream&, TaxiPark&);
	~TaxiPark() {}

    friend class BusyListWindow;
};



