#ifndef DEVICE_H
#define DEVICE_H
#include "devicemanagerizluchatel.h"


class DeviceManagerIzluchatel;

class Device: public QObject
{
public:
    Device(DeviceManagerIzluchatel * iman);




virtual void connectx()=0;
virtual void fireConnected()=0;
virtual void disconnecx()=0;
virtual void ping()=0;
virtual void firePingAccepted()=0;
virtual void measure(int type)=0;


    /**
 * @brief ms relays msg with id and type to devman's acceptMessage
 * @param msg
 * @param id
 * @param type
 *MSG_ERROR
 *MSG_GOOD
 *MSG_NEUTRAL
 */
void ms (QString msg, int id, int type);

void setID (char iid);

bool isConnected;
char id;
DeviceManagerIzluchatel * devman;





};

#endif // DEVICE_H
