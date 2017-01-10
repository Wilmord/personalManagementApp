#ifndef ADDEMPLOYEEDIALOG_H
#define ADDEMPLOYEEDIALOG_H

#include <QDialog>
#include <QAbstractButton>

class QLineEdit;

namespace Ui {
class addEmployeeDialog;
}

enum class EmployeeType{
    Monthly  = 0,
    Hourly   = 1,
    Salesman = 2
};



class addEmployeeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addEmployeeDialog(QWidget *parent = 0);
    ~addEmployeeDialog();

private:
    void setLineEditValidator(QLineEdit* lineEdit, int begin, int end);

private slots:
    void addData();

private:
    Ui::addEmployeeDialog *ui;
    EmployeeType employeetype;
};

#endif // ADDEMPLOYEEDIALOG_H
