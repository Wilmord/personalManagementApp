#include "salesman.h"

Salesman::Salesman(int ssNumber, const QString& name, int mCompensation, double bonus, int realizedOutcome, int outComeThreshold):
  MonthlyPaidEmployee(ssNumber,name,mCompensation),
  m_bonus(bonus),
  m_realizedOutCome(realizedOutcome),
  m_outComeThreshold(outComeThreshold)
{
   m_realizedOutCome >= m_outComeThreshold ? m_outcomeClaim = true : m_outcomeClaim = false;
}

const double Salesman::calculateSalary()
{
    return m_outcomeClaim ? getMonthlyComp() + (getMonthlyComp() * m_bonus) / 100 : getMonthlyComp();
}

void Salesman::setBonus(double bns)
{
    m_bonus = bns;
}

const double Salesman::getBonus()const
{
    return m_bonus;
}

void Salesman::setRealizedOutcome(int outcome)
{
    m_realizedOutCome = outcome;
}

const int Salesman::getRealizedOutcome()const
{
    return m_realizedOutCome;
}

void Salesman::setOutcomeClaim(bool claim)
{
    m_outcomeClaim = claim;
}

const bool Salesman::outcomeClaim()const
{
    return m_outcomeClaim;
}
