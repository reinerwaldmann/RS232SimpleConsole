#ifndef DEVICERS232_H
#define DEVICERS232_H
#include "qextserialport.h"
#include "qextserialenumerator.h"
#include "device.h"

class DeviceRS232 : public Device
{
public:
                    DeviceRS232();

virtual             ~DeviceRS232();

            QString getPosition();

virtual     int    connectx();

            void    setPortname (QString iportname);




virtual     int    disconnecx();


private:
    QextSerialPort * port;
    PortSettings portSettings;




};

#endif // DEVICERS232_H
