#include "devicemanagerizluchatel.h"

DeviceManagerIzluchatel::DeviceManagerIzluchatel(PrincipalWindow *iprincipal, QObject *parent):
    QObject(parent)
{
    principal = iprincipal;
    UI = new DeviceManagerIzluchatelUI (this);

    UI->show();
}


 int DeviceManagerIzluchatel::measure (char slt, char out) //returns 0 if OK, 1 if device is
 {//makes measurements
//for debugging purposes
//principal->shellList.at(slt-1)->acceptResult(slt,out,0,50.1);
//devicesHash.value("s")->connectx();
//for debugging purposes
//devicesHash.value(0)->measure(0);
/*
 *devicesHash.value(0) - is only a controller. Never try to attach
 *measurement device to 0 hashslot
 *
 *In this program (Izluchatel) considering Rubin 201 device the parameter to
 *measure function is always 0.
 *
 *While debugging, the only attached device is slt 0 out 1 which is 1 hash (2*0+1=1)
 **/


     if (!devicesHash.contains(slt*2+out))
     {
         acceptMessage(QString("ERR 2121 DeviceManagerIzluchatel::measure - ERROR: no device under number %1").arg(slt*2+out), 0 , MSG_ERROR );
     }

     return (devicesHash.value(slt*2+out)->measure(0));

 }

 int DeviceManagerIzluchatel::checkAllOK (int number)
    {
        QList <char> keylist = devicesHash.keys();
        char key;
        foreach (key, keylist)
        {
            if (!devicesHash.value(key)->isConnected) return 1;
        }
        if (keylist.size()<number) return 2;
        return 0;

    }

    int DeviceManagerIzluchatel::connectALL ()
    {
        QList <char> keylist = devicesHash.keys();
        char key;
        foreach (key, keylist)
        {
          devicesHash.value(key)->connectx();

        }

        UI->displayDevices();
    }

    int  DeviceManagerIzluchatel::connectx (char id)
    {
        if (!devicesHash.contains(id) )
        {
            acceptMessage("ERR 2151 no such device", 0, MSG_ERROR);
        }
        devicesHash.value(id)->connectx();
        UI->displayDevices();
    }

    int DeviceManagerIzluchatel::disconnectAll ()
    {
        QList <char> keylist = devicesHash.keys();
        char key;
        foreach (key, keylist)
        {
          devicesHash.value(key)->disconnecx();
        }
        UI->displayDevices();

    }

    int DeviceManagerIzluchatel::disconnectx (char id)
    {
        if (!devicesHash.contains(id) )
        {
            acceptMessage("ERR 2171 no such device", 0,  MSG_ERROR);
        }
        devicesHash.value(id)->disconnecx();
        UI->displayDevices();

    }

    int DeviceManagerIzluchatel::acceptMessage (QString msg, int id, int type)
    {
        /*
            here specifies where the message to go after reached this..

        */
        UI->acceptMessage(msg, id, type);

    }

    int DeviceManagerIzluchatel::acceptMeausure(double value, int id, int type)
    {

        UI->acceptMessage(tr ("Accepted measurement data: id = %1, value=%2 %3").arg(QString::number(id)).arg(QString::number(value)).arg(type?"дБ":"дБм"),id,MSG_NEUTRAL );
        //yet all, though then it should go to principal for adding into
        //testing shell

    }


    int DeviceManagerIzluchatel::acceptPing(int id)
    {
        UI->acceptPing(id);
    }


    int DeviceManagerIzluchatel::addDevice (Device * idevice)
    {
        char newid=devicesHash.keys().length();
        idevice->setID(newid);
        devicesHash.insert(newid, idevice);
        //длина списка ключей
        UI->displayDevices();
    }
