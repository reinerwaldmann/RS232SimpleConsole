#ifndef DEVICE_H
#define DEVICE_H
#include "devicemanagerizluchatel.h"
#include <QTimer>

class DeviceManagerIzluchatel;

class Device: public QObject
{

    Q_OBJECT

public:
    Device(DeviceManagerIzluchatel * iman);
    virtual ~Device();




virtual int connectx()=0;
virtual int fireConnected()=0;
virtual int disconnecx()=0;
virtual int ping()=0;
virtual int firePingAccepted()=0;
virtual int measure(int type)=0;
virtual QString getPosition ()=0; //for RS232 it returns port. For LAN - IP


    /**
 * @brief ms relays msg with id and type to devman's acceptMessage
 * @param msg
 * @param id
 * @param type
 *MSG_ERROR
 *MSG_GOOD
 *MSG_NEUTRAL
 */
void ms (QString msg,  int type=MSG_DEBUG);
void setID (char iid);

void setConnectedState (bool iisConnected);


bool isConnected;
char id;
QString name;
QString descr;
DeviceManagerIzluchatel * devman;

QTimer * reqtimer; //таймер, который используется для того, чтоб вывести сообщение "устройство недоступно"


public slots:
void onPingFailed ();


signals:





};

#endif // DEVICE_H
