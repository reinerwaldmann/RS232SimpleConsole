#ifndef DEVICE_H
#define DEVICE_H
#include "devicemanagerizluchatel.h"


class DeviceManagerIzluchatel;

class Device
{
public:
    Device(DeviceManagerIzluchatel * iman);




virtual void connecx()=0;
virtual void fireConnected()=0;
virtual void disconnecx()=0;
virtual void ping()=0;
virtual void firePingAccepted()=0;

void setID (char iid);

bool isConnected;
char id;
DeviceManagerIzluchatel * devman;





};

#endif // DEVICE_H
