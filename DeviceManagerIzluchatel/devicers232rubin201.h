#ifndef DEVICERS232RUBIN201_H
#define DEVICERS232RUBIN201_H
#include "devicers232.h"

class DeviceRS232Rubin201 : public DeviceRS232
{

    Q_OBJECT

public:
    DeviceRS232Rubin201(DeviceManagerIzluchatel *iman);
    ~DeviceRS232Rubin201();

    void setPort (QString iport);

    void connectx();

    void disconnecx();

    void measure(int type);

    void ping ();

    void fireConnected();

    void firePingAccepted();

public slots:
    void onDataAvailable();


};

#endif // DEVICERS232RUBIN201_H
