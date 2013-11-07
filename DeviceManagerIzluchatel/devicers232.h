#ifndef DEVICERS232_H
#define DEVICERS232_H
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "device.h"

class DeviceRS232 : public Device
{
public:

    QextSerialPort * port;
    PortSettings portSettings;
        QString portname;


    DeviceRS232(DeviceManagerIzluchatel * iman);



};

#endif // DEVICERS232_H
