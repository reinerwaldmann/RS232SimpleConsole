#include "devicelanjerome.h"

DeviceLANJerome::DeviceLANJerome():DeviceLAN()
{
port = 2424;
ip="192.168.0.101"; //по умолчанию, вообще говоря, может быть и другой адрес

name = "Jerome";
descr = "Ethernet Controller Kernelchip Jerome";
uniqueType = 201;

}



int DeviceLANJerome::ping ()
{
sendToPort("$KE,PSW,SET,Jerome");
}


//виртуальный слот, объявленный уровнем выше, в deviceLan
/*
Для большей упртсти рекомендуется его объявить в device, но ни к чему не подключать.  - скорее всего, неверно
*/
void DeviceLANJerome::readyRead ()
{
    reqtimer->stop();
    QByteArray ba = socket->readAll();
    QString answer (ba);

    ms(ba, MSG_DEBUG);

    if (ba.contains("PSW,SET,OK"))
    {
        setConnectedState(1);
        return;
    }


}

void DeviceLANJerome::wrLine(int numline, bool state)
{
sendToPort(tr("$KE,WR,%1,%2").arg(numline).arg(state));
}


int DeviceLANJerome::sendToPort(QString msg)
{

DeviceLAN::sendToPort(msg+"\r\n");
}
