#pragma once
//#include <QtCore>
#include "driverDependent.h"
#include "driverIndependent.h"

class BusyListWindow;

class Client;

class TaxiPark {
private:
    QVector<DriverDependent> driversDependent; //зависимые водители (без своего автомобиля)
    QVector<DriverIndependent> driversIndependent; //независимые водители
    Client* m_client{ NULL }; //клиент
    float m_earnMoney; //финансы компании
    void loadData(); //загрузка данных с файла
public:
	TaxiPark() {
		loadData();
	}

    void receiveOrder(Client*); // получение заказа от клиента
    bool completeOrder(QString &, float &, float &, float &, bool); // обработка и выполнение заказа
    TaxiService* findNearestDriver(float&, bool); // поиск ближайшего свободного водителя до клиента
    void busyDriverUpdates(); //обновление статуса зайнятости водителей

    DriverDependent& getDependent(const int);
    DriverIndependent& getIndependent(const int);
    float getCompanyMoney();

    void saveFinancialInfo(); //сохранить финансовую информацию в файлы
    void paySalaries(); //выплата з/п

    void addDependentDriver();
	void addIndependentDriver();

    void setDriverMap(DriverMap*); //передать водителям карту (static)

	friend std::ostream& operator<< (std::ostream&, TaxiPark&);
	~TaxiPark() {}

    friend class BusyListWindow;
};



