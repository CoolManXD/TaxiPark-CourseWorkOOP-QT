#include <iostream>
#include <QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QStringList paths = QCoreApplication::libraryPaths();
        paths.append(".");
        paths.append("imageformats");
        paths.append("platforms");
        paths.append("styles");
    QCoreApplication::setLibraryPaths(paths);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();



//	int chosen;
//	bool BOOL = true;
//	while (BOOL)
//	{
//		system("cls");
//		std::cout << "made by Yanchuk Serhii, IS-82, TaxiPark" << std::endl << std::endl;
//		std::cout << "-----------MENU----------" << std::endl;
//		std::cout << "1 - Make order" << std::endl;
//		std::cout << "2 - Apply for a job" << std::endl;
//		std::cout << "3 - Show drivers' profiles" << std::endl;
//		std::cout << "4 - Pay salaries" << std::endl;
//		std::cout << "5 - Show list of busy drivers" << std::endl;
//		std::cout << "6 - Show list of no busy drivers" << std::endl;
//		std::cout << "0 - exit" << std::endl;
//		std::cout << "Chosen: ";
//		std::cin >> chosen;
//		std::cin.ignore();
//		switch (chosen)
//		{
//		case 1:
//		{
//			park.receiveOrder(new Client{ map });
//			park.completeOrder();
//			std::cout << "Press any key\n";
//			_getch();
//			break;
//		}
//		case 2:
//		{
//			std::cout << "Will you use your car? (+/-)" << std::endl;
//			char what;
//			std::cin >> what;
//			std::cin.ignore();
//			if (what == '+') park.addIndependentDriver();
//			else park.addDependentDriver();
//			std::cout << "Press any key\n";
//			_getch();
//			break;
//		}
//		case 3:
//		{
//			std::cout << park;
//			std::cout << "Press any key\n";
//			_getch();
//			break;
//		}
//		case 4:
//		{
//			park.paySalaries();
//			std::cout << "Press any key\n";
//			_getch();
//			break;
//		}
//		case 5:
//		{
//			park.showListBusyDriver();
//			std::cout << "Press any key\n";
//			_getch();
//			break;
//		}
//		case 6:
//		{
//			park.showListNoBusyDriver();
//			std::cout << "Press any key\n";
//			_getch();
//			break;
//		}
//		case 0:
//		{
//			BOOL = false;
//			std::cout << "Bye bye" << std::endl;
//			std::cout << "Press any key\n";
//			_getch();
//			break;
//		}
//		default:
//		{
//			std::cout << "Ops! Try again!" << std::endl;
//			std::cout << "Press any key" << std::endl;
//			std::cin.clear();
//			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//			break;
//		}
//		}
//	}

//	system("pause");
//	return 0;
}





