#ifndef DEVICERS232RUBIN201_H
#define DEVICERS232RUBIN201_H
#include "devicers232.h"
#include <QTimer>

class DeviceRS232Rubin201 : public DeviceRS232
{

    Q_OBJECT

public:
    //Error code 1
    DeviceRS232Rubin201(DeviceManagerIzluchatel *iman);
    ~DeviceRS232Rubin201();

    //Error code 2
    void setPort (QString iport);

    //Error code 3
    int connectx();

    //Error code 4
    int disconnecx();

    //Error code 5
    int measure(int type);

    //Error code 6
    int ping ();

    //Error code 7
    int fireConnected();

    //Error code 8
    int firePingAccepted();

    //Error code 9
    int sendToPort(QString msg);  //0 if OK 1 if error


    //Error code 10
    int sendToPortMeasureValue();  //0 if OK 1 if error
    //sends 0x82 as a number, fixed




    QByteArray buffer;


       QString getPosition();





public slots:
    //Error code 10
    void onDataAvailable();
    void onPingFired();

};

#endif // DEVICERS232RUBIN201_H
