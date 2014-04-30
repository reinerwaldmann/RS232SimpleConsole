#ifndef DEVICE_H
#define DEVICE_H

#include <QTimer>
#include <qDebug>
#include <QDomNode>

#include <QDomElement>

#include "controller.h"
#include "measurer.h"


#define MSG_ERROR 1
#define MSG_NEUTRAL 0
#define MSG_GOOD 2
#define MSG_DEBUG 3





class Device: public QObject
{
    Q_OBJECT
public:
Device();
virtual ~Device();
virtual int connectx()=0;
virtual int disconnecx()=0;
virtual int ping()=0;

virtual QString getPosition ()=0; //for RS232 it returns port. For LAN - IP
virtual QDomElement  getXMLPOsition (QDomDocument * idoc); //tells the position and other connection parameters in XML format


virtual int configureViaXml (QDomElement iel)=0; //in future this code must form another constructor

//так как иначе сильно ругается при закрытии менеджера, видимо там левое устройство или не может выбрать правильно метод





void setID (int iid);
int getID();

int  getUniqueType();


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

int id;
QString name;
QString variableComment;
QString descr;
QTimer * reqtimer; //таймер, который используется для таймаутов
int type; //1 - RS232 2- LAN

int uniqueType; //уникальный идентификатор типа устройства

int timeout; //in milliseconds
virtual void setConnectedState (bool isState);


bool portIsSearched;  //when up, then slot 'disconnected' not to be activated

bool isConnected;








public slots:
void onPingFailed ();
void slotConnectx ();



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
