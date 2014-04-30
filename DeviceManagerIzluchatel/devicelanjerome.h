#ifndef DEVICELANJEROME_H
#define DEVICELANJEROME_H
#include "devicelan.h"


class DeviceLANJerome : public DeviceLAN, Controller
{
public:
    DeviceLANJerome();
     int ping ();

    //Джеромоспецифичное
     //устанавливает уровень на линии, команда $KE,WR, <line>, <state>
     void wrLine(int numline, bool state=1);
     int sendToPort(QString msg);



private slots:
    void readyRead ();


};

#endif // DEVICELANJEROME_H


