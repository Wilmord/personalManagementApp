#ifndef MONTHLYPAIDEMPLOYEE_H
#define MONTHLYPAIDEMPLOYEE_H

#include "personnel.h"

class MonthlyPaidEmployee : public Personnel
{
public:
    explicit MonthlyPaidEmployee(int ssNumber, const QString& name, int mCompensation);
    void setMonthlyCompensation(const QString& compensation);

    const double calculateSalary() override;

    void setMonthlyComp(int compensation);
    const int getMonthlyComp()const;

private:
    int m_MonthlyCompensation;

};

#endif // MONTHLYPAIDEMPLOYEE_H
