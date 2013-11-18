#include "device.h"

Device::Device(DeviceManagerIzluchatel *iman)
{

    devman = iman;
    isConnected=0;
    id=INT_MAX; //если в ходе выполнения выплывает это значение,
    //это значит, что айди не присвоен почему-то

    reqtimer = new QTimer (this);
    connect (reqtimer, SIGNAL ( timeout()  ), this, SLOT (onPingFailed()) );

       reqtimer->setSingleShot(1);
}



void Device::setID(char iid)
{
    id = iid;

}


void Device::setConnectedState (bool iisConnected)
{
isConnected=iisConnected;
devman->UI->displayDevices();

}


void Device::ms (QString msg,  int type)
{
    devman->acceptMessage(msg, id, type);

}



void Device::onPingFailed()
{

    devman->acceptPingFailed(id);
    //devman->acceptMessage(tr("Ошибка: Не отвечает на запросы"),id,  MSG_ERROR);
    setConnectedState(0);

}
