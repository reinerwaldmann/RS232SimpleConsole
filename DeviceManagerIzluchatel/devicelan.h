#ifndef DEVICELAN_H
#define DEVICELAN_H

#include "device.h"
#include <QTcpSocket>
#include <QTimer>

class DeviceLAN : public Device
{
    Q_OBJECT

public:
    DeviceLAN();
    virtual ~DeviceLAN ();
    QString getPosition (); //for RS232 it returns port. For LAN - IP
    QDomElement  getXMLPOsition (QDomDocument * idoc); //tells the position and other connection parameters in XML format
    int connectx();
    virtual int sendToPort(QString msg);
    int disconnecx();

    virtual int configureViaXml (QDomElement iel); //in future this code must form another constructor





protected:
    QString ip;
    int port;
    QTcpSocket  * socket;




public slots:


    virtual void readyRead ()=0;
    void getConnected();
    void displayError(QAbstractSocket::SocketError socketError);

};

#endif // DEVICELAN_H
