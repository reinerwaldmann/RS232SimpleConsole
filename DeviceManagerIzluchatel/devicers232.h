#ifndef DEVICERS232_H
#define DEVICERS232_H
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "device.h"
#include <QDebug>

class DeviceRS232 : public Device
{
public:
                    DeviceRS232();

virtual             ~DeviceRS232();

            QString getPosition();

virtual     int    connectx();

            void    setPortname (QString iportname);


virtual void supersearch (QList<QextPortInfo> inlist);

virtual void search ();

virtual     int    disconnecx();



virtual int configureViaXml (QDomElement iel);




protected:
    QextSerialPort * port;
    PortSettings portSettings;


    int idInSearchList;
    QList<QextPortInfo> searchPortLst;

    virtual void setConnectedState (bool isState);


};

#endif // DEVICERS232_H
