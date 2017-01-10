#include "personnel.h"

Personnel::Personnel(int ssNumber, const QString& name, QObject *parent) :
    QObject(parent),
    m_SSN(ssNumber),
    m_Name(name)
{

}

Personnel::~Personnel()
{ }

void Personnel::setSSN(int SSN)
{
    m_SSN = SSN;
}

void Personnel::setName(const QString& name)
{
    m_Name = name;
}

const int Personnel::getSSN()const
{
    return m_SSN;
}

const QString& Personnel::getName()const
{
    return m_Name;
}
