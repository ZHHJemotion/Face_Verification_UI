#include "mainwindow.h"
#include <QApplication>
#include <QDebug>

//#include </usr/include/c++/4.2.1/cmath>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
