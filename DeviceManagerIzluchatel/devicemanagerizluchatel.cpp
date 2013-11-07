#include "devicemanagerizluchatel.h"

DeviceManagerIzluchatel::DeviceManagerIzluchatel(PrincipalWindow *iprincipal, QObject *parent):
    QObject(parent)
{

    principal = iprincipal;


}


 char DeviceManagerIzluchatel::measure (char slt, char out) //returns 0 if OK, 1 if device is
 {//makes measurements
//for debugging purposes

principal->shellList.at(slt-1)->acceptResult(slt,out,0,50.1);

return 0;

 }




    bool DeviceManagerIzluchatel::checkAllOK ()
    {}

    void DeviceManagerIzluchatel::connectALL ()
    {}

    void DeviceManagerIzluchatel::connectx (char id)
    {}

    void DeviceManagerIzluchatel::disconnectAll ()
    {}

    void DeviceManagerIzluchatel::disconnectx (char id)
    {}

    void DeviceManagerIzluchatel::acceptMessage (QString msg, int id, int type)
    {}

    char DeviceManagerIzluchatel::addDevice (Device * idevice)
    {}
