#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "hourlycompensationemployee.h"
#include "salesman.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    addDialog(new addEmployeeDialog(this)),
    columnCount(3)
{
    ui->setupUi(this);

    this->setWindowTitle(QLatin1String("Personal Management Application"));


    ui->employeeListTableWidget->setColumnCount(columnCount);
    QHeaderView* headers = ui->employeeListTableWidget->horizontalHeader();
    headers->setSectionResizeMode(QHeaderView::Stretch);

    m_TableHeader<<QLatin1String("SSN")<<QLatin1String("Name")<<QLatin1String("Salary");
    ui->employeeListTableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->employeeListTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);

    connect(ui->addEmployeePushButton,&QPushButton::clicked,[this](){
        showEmployeeAddWidget();
    });

    connect(ui->removeEmployeePushButton,&QPushButton::clicked,[this](){
        removeEmployeeFromTable();
    });


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillEmployeeTable(const QVector<Personnel*>& employeeList)
{
        int rowCount = employeeList.count();
        if(rowCount == 0)
            return;
        else
            ui->employeeListTableWidget->setRowCount(rowCount);

        for(int i = 0; i < rowCount; ++i)
        {
            for(int j = 0; j < columnCount; ++j)
            {
               addEmployee(employeeList.at(i),i,j);
            }
        }
}


void MainWindow::addEmployee(Personnel* p,int i, int j)
{
    QTableWidgetItem *newItem = new QTableWidgetItem;
    ui->employeeListTableWidget->setItem(i, j, newItem); //ownership passes to table
    ui->employeeListTableWidget->item(i,j)->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

    if(j == static_cast<int>(ColumnType::id))
        ui->employeeListTableWidget->item(i,j)->setText(QString::number(p->getSSN()));
    else if(j == static_cast<int>(ColumnType::name))
        ui->employeeListTableWidget->item(i,j)->setText(p->getName());
    else
        ui->employeeListTableWidget->item(i,j)->setText(QString::number(p->calculateSalary()));

}

void MainWindow::showEmployeeAddWidget()
{
  //create add employee widget
   if(addDialog->exec())
   {
       //add employee
   }
   else
   {
       //cancel
   }

}

 void MainWindow::removeEmployeeFromTable()
 {
     QList<QTableWidgetItem*> selectedRows = ui->employeeListTableWidget->selectedItems();
     while(!selectedRows.isEmpty())
     {
         ui->employeeListTableWidget->removeRow(selectedRows.at(0)->row());
         selectedRows = ui->employeeListTableWidget->selectedItems();
     }
 }


 void MainWindow::employeeInfoGetter(const EmployeeType type, const int ssn, const QString& name, const int mCompensation, const int hCompensation, const double doneHours, const double bonus,const int realizedOutcome )
 {
     Personnel* p;
     if(type == EmployeeType::Salesman)
     {
         p = new Salesman(ssn,name,mCompensation,bonus,realizedOutcome);
     }
     else if(type == EmployeeType::Hourly)
     {
        p = new HourlyCompensationEmployee(ssn,name,hCompensation,doneHours);
     }
     else //if(type == EmployeeType::Monthly)
     {
        p = new MonthlyPaidEmployee(ssn,name,mCompensation);
     }

     ui->employeeListTableWidget->insertRow(ui->employeeListTableWidget->rowCount());
     for(int j = 0; j < columnCount; ++j)
     {
       addEmployee(p,ui->employeeListTableWidget->rowCount()-1,j);
     }

 }









