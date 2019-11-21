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
}





