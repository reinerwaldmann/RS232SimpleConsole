#include "device.h"

Device::Device(DeviceManagerIzluchatel *iman)
{

    devman = iman;
}

void Device::setID(char iid)
{
    id = iid;

}
