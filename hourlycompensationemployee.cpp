#include "hourlycompensationemployee.h"

HourlyCompensationEmployee::HourlyCompensationEmployee(int ssNumber, const QString& name, int hCompensation,double doneHours):
  Personnel(ssNumber,name),
  m_HourlyCompensation(hCompensation),
  m_DoneHours(doneHours)
{

}

const double HourlyCompensationEmployee::calculateSalary()
{
  return m_DoneHours * m_HourlyCompensation;
}

void HourlyCompensationEmployee::setHourlyComp(int compensation)
{
    m_HourlyCompensation = compensation;
}

const int HourlyCompensationEmployee::getHourlyComp()const
{
  return m_HourlyCompensation;
}

void HourlyCompensationEmployee::setDoneHours(int hours)
{
    m_DoneHours = hours;
}

const int HourlyCompensationEmployee::getDoneHours()const
{
    return m_DoneHours;
}
