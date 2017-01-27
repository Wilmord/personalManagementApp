#include "mainwindow.h"
#include <QApplication>

#include "hourlycompensationemployee.h"
#include "salesman.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QVector<Personnel*> data;
    data.push_back(new MonthlyPaidEmployee(12345,"Joe Black", 1000));
    data.push_back(new HourlyCompensationEmployee(12234,"Juliana Crain", 20,100));
    data.push_back(new Salesman(11156,"Lem Washington", 3000,12,3000,10));


    MainWindow w;

    w.fillEmployeeTable(data);

    w.show();

    return a.exec();
}
