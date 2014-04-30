#ifndef MEASURER_H
#define MEASURER_H

#include <QString>
/**
 * @brief The Measurer class
 * Класс, от которого наследуются измерители
 */

class Measurer
{
public:
    Measurer();
    virtual int measure(QString type="")=0;
};

#endif // MEASURER_H
