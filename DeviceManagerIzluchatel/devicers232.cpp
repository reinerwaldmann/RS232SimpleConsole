#include "devicers232.h"

DeviceRS232::DeviceRS232()
{
type=1; //RS232

descr="RS232 device";

timeout=2000;


}


DeviceRS232::~DeviceRS232()
{
    disconnecx();

}

QString DeviceRS232::getPosition()
{
    return port->portName();
}

void DeviceRS232::setPortname(QString iportname)
{
    port->setPortName(iportname);

}


int DeviceRS232::connectx()
{
    if (!port->portName().length())
    {
        ms(tr ("ERR DeviceRS232 no portname specified"), MSG_ERROR);

        return 1;
    }

    //port->setPortName(portname);
    if (port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
    {
    ms(tr ("MSG DeviceRS232 Port %1 successfully opened").arg (port->portName()), MSG_DEBUG);
    }
    else
    {
    ms(tr ("ERR DeviceRS232 Port %1 error while opening").arg (port->portName()), MSG_ERROR);
    return 2;
    }
    return ping();
}


int DeviceRS232::disconnecx()
{
port->close();
setConnectedState(0);
}


void DeviceRS232::supersearch (QList<QextPortInfo> inlist)
{
    //суперметод, запускаем процесс поиска
idInSearchList=-1;

portIsSearched=1;
searchPortLst = inlist;





search();


}

void DeviceRS232::search ()
{
    //подметод

    idInSearchList++;
    if (idInSearchList>=inlist.size())
    {
        //ругнулись на то, что найти не удалось
        ms(tr ("Найти устройство не вышло id=%1").arg(id), MSG_ERROR);
        portIsSearched=0;//сняли флаг поиска, так как поиск завершён, пусть и неудачей
        searchPortLst.clear(); //чтоб даже искать не пытался вдруг
        return;

    }


    //собственно действия - напишем их завтра, так как уже пора домой!






}
