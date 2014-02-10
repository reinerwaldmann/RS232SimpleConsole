#ifndef DEVICE_H
#define DEVICE_H
#include "devicemanagerizluchatel.h"
#include <QTimer>

class DeviceManagerIzluchatel;

class Device: public QObject
{
    Q_OBJECT
public:
Device();
virtual ~Device();
virtual int connectx()=0;
virtual int disconnecx()=0;
virtual int ping()=0;
virtual int measure(QString type="")=0;
virtual QString getPosition ()=0; //for RS232 it returns port. For LAN - IP

void setID (int iid);
int getID();

bool getIsConnected();

QString getName();

QString getDescription();

QString getVariableComment();
void setVariableComment(QString iVariableComment);

int getType();

int getTimeout();

void ms(QString imsg, int type);

Device * returnMe();



protected:
bool isConnected;
int id;
QString name;
QString variableComment;
QString descr;
QTimer * reqtimer; //таймер, который используется для таймаутов
int type; //1 - RS232
int timeout; //in milliseconds
void setConnectedState (bool isState);



public slots:
void onPingFailed ();



signals:
void fireConnected(int id);
///void firePingAccepted(int id);
void fireDisconnected(int id);
void fireMeasurementData (int id, double data, QString type);
void fireMsg (int id, QString imsg,  int type=MSG_DEBUG);

/**
* @brief ms relays msg with id and type to devman's acceptMessage
* @param msg
* @param id
* @param type
*MSG_ERROR
*MSG_GOOD
*MSG_NEUTRAL
*/


};

#endif // DEVICE_H
