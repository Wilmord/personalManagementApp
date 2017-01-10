#ifndef SALESMAN_H
#define SALESMAN_H

#include "monthlypaidemployee.h"

class Salesman : public MonthlyPaidEmployee
{
public:
    explicit Salesman(int ssNumber, const QString& name, int mCompensation, double bonus, int realizedOutcome, int outComeThreshold = 20);

    const double calculateSalary() override;

    void setBonus(double bns);
    const double getBonus()const;

    void setRealizedOutcome(int outcome);
    const int getRealizedOutcome()const;

    void setOutcomeClaim(bool claim);
    const bool outcomeClaim()const;

private:
    double m_bonus;
    bool   m_outcomeClaim;
    int    m_realizedOutCome, m_outComeThreshold; //There is an asssumption here, if salesman passes threshold, he/she will get bonus.
};

#endif // SALESMAN_H
