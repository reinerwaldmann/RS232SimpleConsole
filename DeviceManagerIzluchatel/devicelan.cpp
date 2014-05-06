#include "devicelan.h"

DeviceLAN::DeviceLAN()
{
    socket = new QTcpSocket (this);
    connect(socket, SIGNAL(readyRead()),this, SLOT(readyRead()));
     connect(socket, SIGNAL(connected()), this, SLOT(getConnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));
    type=2; //LAN
}


DeviceLAN::~DeviceLAN ()
{
if  (isConnected ) disconnecx();
//delete socket;
}



QString DeviceLAN::getPosition()
{

return tr("%1:%2").arg(ip).arg(QString::number(port));
}


QDomElement  DeviceLAN::getXMLPOsition (QDomDocument * idoc) //tells the position and other connection parameters in XML format
{
    QDomElement node = Device::getXMLPOsition(idoc);

    QDomElement val = idoc->createElement("ip");
    QDomText txt = idoc->createTextNode(ip) ;
    val.appendChild(txt);
    node.appendChild(val);

    QDomElement val1 = idoc->createElement("port");
    QDomText txt1 = idoc->createTextNode(QString::number(port)) ;
    val1.appendChild(txt1);
    node.appendChild(val1);

    return node;

}

int DeviceLAN::connectx()
{

    if (!isConnected)
    {    socket->connectToHost(ip, port);}
    else
    {  ping(); }

    return 1;



/*
Из-за особенностей реализации QtcpSocket: он при подключении вызывает getConnected, где и есть вызов ping.
Соответственно, таймер, ждущий открытия порта, здесь не требуется.
*/
//return ping(); //для единообразия с RS232, хотя нафихх не нужен, да
}




void DeviceLAN::getConnected() //отрабатывает, когда подключится
{
ping(); //вызов вот этого обязателен, ибо именно ping посылает команду с паролем на устройство
}

void DeviceLAN::displayError(QAbstractSocket::SocketError socketError) //отрабатывает, когда косяк
{
    reqtimer->stop();
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        ms("Remote host closed connection",MSG_ERROR);
        break;
    case QAbstractSocket::HostNotFoundError:
        ms("Error: Host not found", MSG_ERROR);

        break;
    case QAbstractSocket::ConnectionRefusedError:
        ms ("Error: Connection refused", MSG_ERROR);
        break;
    default:
        ms("Error: unknown"+QString::number(socketError), MSG_ERROR);
    }
    setConnectedState(0);
}


int DeviceLAN::sendToPort(QString msg)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(5);
    //if(msg!="") msg=","+msg; //only for Jerome

    //QString msg1="$KE"+msg+"\r\n";
        //      out << prefix.toAscii()<</*<<message <<*/ (quint16)0x0D <<(quint16)0x0A;
              //out << prefix.toAscii()<</*<<message <<*/ 0x0D << 0x0A;
    //QByteArray blockx = msg.toAscii();
    QByteArray blockx = msg.toLatin1();
    reqtimer->start(timeout);
    return socket->write(blockx);


}

int DeviceLAN::disconnecx()
{
    socket->close();
    setConnectedState(0);

}


int DeviceLAN::configureViaXml (QDomElement iel) //in future this code must form another constructor
{
//конфигуратор из xml

    QDomNodeList nodeList = iel.elementsByTagName("ip");
    if (nodeList.isEmpty())
    {
        ms("Error: no ip section in XML", MSG_ERROR);
        return 1;
    }


    QDomNodeList nodeListPort = iel.elementsByTagName("port");
    if (nodeListPort.isEmpty())
    {
        ms("Error: no port section in XML", MSG_ERROR);
        return 1;
    }


    QString ipex = nodeList.at(0).toElement().childNodes().at(0).toText().data();
    QString portex = nodeListPort.at(0).toElement().childNodes().at(0).toText().data();



    ms (ipex,MSG_DEBUG);
    ms (portex,MSG_DEBUG);


    if (ipex.isEmpty())
    {
        ms("Error: ip section in XML is empty", MSG_ERROR);
        return 1;
    }
    if (portex.isEmpty())
    {
        ms("Error: port section in XML is empty", MSG_ERROR);
        return 1;
    }



    ip = ipex;
    port = portex.toInt();


}


