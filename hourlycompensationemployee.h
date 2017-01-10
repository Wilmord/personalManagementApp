#ifndef HOURLYCOMPENSATIONEMPLOYEE_H
#define HOURLYCOMPENSATIONEMPLOYEE_H

#include "personnel.h"

class HourlyCompensationEmployee : public Personnel
{
public:
    explicit HourlyCompensationEmployee(int ssNumber, const QString& name, int hCompensation, double doneHours);
    void setHourlyCompensation(const QString& compensation);

    const double calculateSalary() override;

    void setHourlyComp(int compensation);
    const int getHourlyComp()const;
    void setDoneHours(int hours);
    const int getDoneHours()const;

private:
    int m_HourlyCompensation;
    double m_DoneHours;
};

#endif // HOURLYCOMPENSATIONEMPLOYEE_H
