#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

#include "addEmployeeDialog.h"

class Personnel;
class QGridLayout;

namespace Ui {
class MainWindow;
}

enum class ColumnType{
    id     = 0,
    name   = 1,
    salary = 2
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void fillEmployeeTable(const QVector<Personnel*>& employeeList);
    //void employeeInfoGetter(const EmployeeType type, const int ssn, const QString& name, const int mCompensation, const int hCompensation, const double doneHours, const double bonus,const int realizedOutcome);
private:
    void showEmployeeAddWidget();
    void addEmployee(Personnel* p, int i, int j);
    void addEmployeeFromUser();
    void removeEmployeeFromTable();
    void createInfoWidget(const int row);
    void clearEmployeeInfoWidget();
    void createLabelAndLineEdit(const QString& labelStr, const QString& lineEditStr,QGridLayout* ly,int position);
    void saveList();
private:
    Ui::MainWindow* ui;

    addEmployeeDialog* addDialog;

    int columnCount;
    QStringList m_TableHeader;
    QVector<Personnel*> personalList;
};

#endif // MAINWINDOW_H
