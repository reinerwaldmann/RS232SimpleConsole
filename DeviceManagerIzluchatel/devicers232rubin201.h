#ifndef DEVICERS232RUBIN201_H
#define DEVICERS232RUBIN201_H
#include "devicers232.h"
#include <QTimer>
#include <qDebug>

class DeviceRS232Rubin201 : public DeviceRS232
{

    Q_OBJECT

public:
    //Error code 1
    DeviceRS232Rubin201();
    ~DeviceRS232Rubin201();



    //Error code 5
    int measure(QString type="");

    //Error code 6
    int ping ();

    //Error code 7
    //int fireConnected();

    //Error code 8
   // int firePingAccepted();

    //Error code 9
    int sendToPort(QString msg);  //0 if OK 1 if error


    //Error code 10
    int sendToPortMeasureValue();  //0 if OK 1 if error
    //sends 0x82 as a number, fixed




    QByteArray buffer;



private:

    bool waitingForConnect; // for to separate measurements from just pinging
    //1 is waiting 0 is not waiting



public slots:
    //Error code 10
    void onDataAvailable();
    void onPingFired();



};

#endif // DEVICERS232RUBIN201_H
