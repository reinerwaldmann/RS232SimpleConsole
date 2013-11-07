#include "device.h"

Device::Device(DeviceManagerIzluchatel *iman)
{

    devman = iman;
    isConnected=0;
    id=INT_MAX; //если в ходе выполнения выплывает это значение,
    //это значит, что айди не присвоен почему-то



}

void Device::setID(char iid)
{
    id = iid;

}


void Device::ms (QString msg, int id, int type)
{
    devman->acceptMessage(msg, id, type);

}
