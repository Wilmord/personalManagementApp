#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <QObject>

class Personnel : public QObject
{
    Q_OBJECT

public:
    explicit Personnel(int ssNumber, const QString& name,QObject *parent = 0);
    virtual  ~Personnel();

    virtual const double calculateSalary() = 0;

    void setSSN(int SSN);
    void setName(const QString& name);
    const int  getSSN()const;
    const QString& getName()const;

private:
  int m_SSN;
  QString m_Name;
};

#endif // PERSONNEL_H
