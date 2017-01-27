#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QLineEdit>
#include <QXmlStreamWriter>
#include <QFile>
#include <QMessageBox>

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

    connect(ui->savePushButton,&QPushButton::clicked,[this](){
        saveList();
    });

    //TODO: any row selected, create info widget dynamically
    connect(ui->employeeListTableWidget,&QTableWidget::cellClicked,[this](int rw){
        createInfoWidget(rw);
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
            personalList.push_back(employeeList.at(i));
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
   if(addDialog->exec())
   {
        addEmployeeFromUser();
   }

}

void MainWindow::removeEmployeeFromTable()
{
    QList<QTableWidgetItem*> selectedRows = ui->employeeListTableWidget->selectedItems();
    while(!selectedRows.isEmpty())
    {
        personalList.removeAt(selectedRows.at(0)->row());
        ui->employeeListTableWidget->removeRow(selectedRows.at(0)->row());
        selectedRows = ui->employeeListTableWidget->selectedItems();
    }
}


void MainWindow::addEmployeeFromUser()
{
    EmployeeType type;
    int          ssn;
    QString      name;
    int          mCompensation;
    int          hCompensation;
    double       doneHours;
    double       bonus;
    int          realizedOutcome;
    addDialog->newEmployee(type,ssn, name, mCompensation,hCompensation,doneHours,bonus,realizedOutcome);

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

    personalList.push_back(p);
}



void MainWindow::createInfoWidget(const int row)
{
    clearEmployeeInfoWidget();

    QGridLayout* gridLayout = new QGridLayout;

    createLabelAndLineEdit(QStringLiteral("Name:"),personalList.at(row)->getName(),gridLayout,0);
    createLabelAndLineEdit(QStringLiteral("SSN:"),QString::number(personalList.at(row)->getSSN()),gridLayout,1);

    ui->employeeInfoWidget->setLayout(gridLayout);
}


void MainWindow::createLabelAndLineEdit(const QString& labelStr, const QString& lineEditStr,QGridLayout* ly,int position)
{
    QLabel* label = new QLabel(labelStr,this);
    QLineEdit* lineEdit = new QLineEdit(lineEditStr,this);
    lineEdit->setReadOnly(true);

    ly->addWidget(label,position,0);
    ly->addWidget(lineEdit,position,1);
}

void MainWindow::clearEmployeeInfoWidget()
{
    foreach (QWidget *w, ui->employeeInfoWidget->findChildren<QWidget*>())
        delete w;

    if(ui->employeeInfoWidget->layout())
    {
        QLayoutItem* ly_item;
        while(( ly_item = ui->employeeInfoWidget->layout()->takeAt(0)) != nullptr )
            delete ly_item;
        delete ui->employeeInfoWidget->layout();
     }
}

void MainWindow::saveList()
{
    QXmlStreamWriter xmlWriter;
    QFile file("Personal_List.xml");
    if (!file.open(QIODevice::WriteOnly))
    {
       QMessageBox::warning(0, "Error!", "Error opening file");
    }
    else
    {
        xmlWriter.setDevice(&file);
        /* Writes a document start with the XML version number. */
        xmlWriter.writeStartDocument();
        xmlWriter.writeCharacters("\n");
        xmlWriter.writeStartElement("Employees");
        xmlWriter.writeCharacters("\n");
        foreach (const auto p, personalList)
        {
            xmlWriter.writeCharacters("\t");
            xmlWriter.writeStartElement("Employee");
            xmlWriter.writeAttribute("SSN",QString::number(p->getSSN()));
            xmlWriter.writeAttribute("name",p->getName());

            auto salesEmployee = dynamic_cast<Salesman*>(p);
            if(salesEmployee)
            {
                xmlWriter.writeAttribute("Monthly Compensation",QString::number(salesEmployee->getMonthlyComp()));
                xmlWriter.writeAttribute("Bonus",QString::number(salesEmployee->getBonus()));
                xmlWriter.writeAttribute("Realized outcome",QString::number(salesEmployee->getRealizedOutcome()));
                xmlWriter.writeAttribute("Outcome claim",QString::number(salesEmployee->outcomeClaim()));
                xmlWriter.writeAttribute("Salary",QString::number(salesEmployee->calculateSalary()));
                xmlWriter.writeEndElement();
                xmlWriter.writeCharacters("\n");
                continue;
            }

            auto hEmployee = dynamic_cast<HourlyCompensationEmployee*>(p);
            if(hEmployee)
            {
                xmlWriter.writeAttribute("Hourly Compensation",QString::number(hEmployee->getHourlyComp()));
                xmlWriter.writeAttribute("Done Hours",QString::number(hEmployee->getHourlyComp()));
                xmlWriter.writeAttribute("Salary",QString::number(hEmployee->calculateSalary()));
                xmlWriter.writeEndElement();
                xmlWriter.writeCharacters("\n");
                continue;
            }

            auto mEmployee = dynamic_cast<MonthlyPaidEmployee*>(p);
            if(mEmployee)
            {
                xmlWriter.writeAttribute("Monthly Compensation",QString::number(mEmployee->getMonthlyComp()));
                xmlWriter.writeAttribute("Salary",QString::number(mEmployee->calculateSalary()));
                xmlWriter.writeEndElement();
                xmlWriter.writeCharacters("\n");
                continue;
            }

            /*close tag student  */
            xmlWriter.writeEndElement();
            xmlWriter.writeCharacters("\n");
        }


        /*end tag students*/
        xmlWriter.writeEndElement();
        /*end document */
        xmlWriter.writeEndDocument();
    }

}


