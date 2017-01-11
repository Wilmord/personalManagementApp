#include "addEmployeeDialog.h"
#include "ui_addemployeedialog.h"

#include <QLineEdit>

const int lowerBound = 0;
const int upperBound = 1000000;



addEmployeeDialog::addEmployeeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addEmployeeDialog),
    employeetype(EmployeeType::Monthly)
{
    ui->setupUi(this);

    ui->monthlyRadioButton->setChecked(true);
    ui->hourlyCompLineEdit->setDisabled(true);
    ui->doneHoursLineEdit->setDisabled(true);
    ui->bonusLineEdit->setDisabled(true);
    ui->realizedOutcomeLineEdit->setDisabled(true);

    setLineEditValidator(ui->monthlyCompLineEdit,lowerBound,upperBound);
    setLineEditValidator(ui->hourlyCompLineEdit,lowerBound,upperBound);
    setLineEditValidator(ui->bonusLineEdit,lowerBound,upperBound);
    setLineEditValidator(ui->realizedOutcomeLineEdit,lowerBound,upperBound);

    connect(ui->monthlyRadioButton,static_cast<void(QRadioButton::*)(bool)>(&QRadioButton::clicked),[this](bool clicked){
        if(clicked == true)
         {
            employeetype = EmployeeType::Monthly;
            ui->hourlyCompLineEdit->setDisabled(true);
            ui->doneHoursLineEdit->setDisabled(true);
            ui->bonusLineEdit->setDisabled(true);
            ui->realizedOutcomeLineEdit->setDisabled(true);

            ui->hourlyCompLineEdit->setText("");
            ui->doneHoursLineEdit->setText("");
            ui->bonusLineEdit->setText("");
            ui->realizedOutcomeLineEdit->setText("");
         }
    });

    connect(ui->hourlyRadioButton,static_cast<void(QRadioButton::*)(bool)>(&QRadioButton::clicked),[this](bool clicked){
        if(clicked == true)
        {
            employeetype = EmployeeType::Hourly;
            ui->hourlyCompLineEdit->setDisabled(false);
            ui->doneHoursLineEdit->setDisabled(false);
            ui->bonusLineEdit->setDisabled(true);
            ui->realizedOutcomeLineEdit->setDisabled(true);

            ui->bonusLineEdit->setText("");
            ui->realizedOutcomeLineEdit->setText("");
        }
    });

    connect(ui->salesManRadioButton,static_cast<void(QRadioButton::*)(bool)>(&QRadioButton::clicked),[this](bool clicked){
        if(clicked == true)
        {
           employeetype = EmployeeType::Salesman;
           ui->doneHoursLineEdit->setDisabled(true);
           ui->hourlyCompLineEdit->setDisabled(false);
           ui->bonusLineEdit->setDisabled(false);
           ui->realizedOutcomeLineEdit->setDisabled(false);

            ui->doneHoursLineEdit->setText("");
        }
    });

    connect(ui->okPushButton,SIGNAL(clicked()),this,SLOT(accept()));
    connect(ui->cancelPushButton,SIGNAL(clicked()),this,SLOT(reject()));

}

addEmployeeDialog::~addEmployeeDialog()
{
    delete ui;
}

void addEmployeeDialog::setLineEditValidator(QLineEdit* lineEdit, int begin, int end)
{
    QIntValidator* validator = new QIntValidator(begin,end,lineEdit);
    lineEdit->setValidator(validator);
}

int addEmployeeDialog::exec()
{
    ui->monthlyRadioButton->setChecked(true);
    ui->ssnLineEdit->setText("");
    ui->nameLineEdit->setText("");
    ui->monthlyCompLineEdit->setText("");
    ui->hourlyCompLineEdit->setText("");
    ui->doneHoursLineEdit->setText("");
    ui->bonusLineEdit->setText("");
    ui->realizedOutcomeLineEdit->setText("");

    employeetype = EmployeeType::Monthly;

    return QDialog::exec();
}

void addEmployeeDialog::newEmployee(EmployeeType& type, int& ssn, QString& name, int& mCompensation, int& hCompensation, double& doneHours, double& bonus, int& realizedOutcome)
{
    type             = employeetype;
    ssn              = ui->ssnLineEdit->text().toInt();
    name             = ui->nameLineEdit->text();
    mCompensation    = ui->monthlyCompLineEdit->text().toInt();
    hCompensation    = ui->hourlyCompLineEdit->text().toInt();
    doneHours        = ui->doneHoursLineEdit->text().toDouble();
    bonus            = ui->bonusLineEdit->text().toDouble();
    realizedOutcome  = ui->realizedOutcomeLineEdit->text().toInt();
}

