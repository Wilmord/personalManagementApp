#include "monthlypaidemployee.h"

MonthlyPaidEmployee::MonthlyPaidEmployee(int ssNumber, const QString& name, int mCompensation):
  Personnel(ssNumber,name),
  m_MonthlyCompensation(mCompensation)
{

}

const double MonthlyPaidEmployee::calculateSalary()
{
  return m_MonthlyCompensation;
}

void MonthlyPaidEmployee::setMonthlyComp(int compensation)
{
    m_MonthlyCompensation = compensation;
}

const int MonthlyPaidEmployee::getMonthlyComp()const
{
  return m_MonthlyCompensation;
}
