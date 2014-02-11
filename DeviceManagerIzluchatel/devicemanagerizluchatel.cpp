#include "devicemanagerizluchatel.h"

DeviceManagerIzluchatel::DeviceManagerIzluchatel(PrincipalWindow *iprincipal, QObject *parent):
    QObject(parent)
{
    principal = iprincipal;
    UI = new DeviceManagerIzluchatelUI (this);
    UI->show();
}


DeviceManagerIzluchatel::~DeviceManagerIzluchatel ()
{

        QList <int> keylist = devicesHash.keys();
        char key;
        foreach (key, keylist)
        {
            devicesHash.value(key)->disconnecx();
            delete devicesHash.value(key);
        }

    devicesHash.clear();
}


 int DeviceManagerIzluchatel::measure (int id, QString type)//returns 0 if OK, 1 if device is
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

     if (!devicesHash.contains(id)) {return 1;}
     return (devicesHash.value(id)->measure(type));

 }

 int DeviceManagerIzluchatel::checkAllOK ()
    {
        QList <int> keylist = devicesHash.keys();
        char key;
        foreach (key, keylist)
        {
            if (!devicesHash.value(key)->getIsConnected()) return 1;
        }
        return 0;

    }

    int DeviceManagerIzluchatel::connectALL ()
    {
        QList <int> keylist = devicesHash.keys();
        char key;
        foreach (key, keylist)
        {
          devicesHash.value(key)->connectx();

        }


        return 0 ;
    }

    int DeviceManagerIzluchatel::disconnectAll ()
    {
        QList <int> keylist = devicesHash.keys();
        char key;
        foreach (key, keylist)
        {
          devicesHash.value(key)->disconnecx();
        }
        UI->displayDevices();

    }


    /*

*/
    int DeviceManagerIzluchatel::addDevice(Device *idevice, int desiredid)
    {
        int newid = desiredid;

        if (!desiredid)
        {
            newid=devicesHash.keys().length()+1;
        }


        idevice->setID(newid);
        devicesHash.insert(newid, idevice);
        UI->displayDevices(); //прямой вызов к интерфейсу, может быть заменён на связь сигнал-слот
        connect (idevice, SIGNAL (fireConnected (int)), this, SLOT (slotAcceptDeviceConnected(int))  );
        connect (idevice, SIGNAL (fireDisconnected (int)), this, SLOT (slotAcceptDeviceDisconnected(int))  );
        connect (idevice, SIGNAL (fireMeasurementData (int, double, QString)), this, SLOT (slotAcceptMeausure(int,double, QString))  );
        connect (idevice, SIGNAL (fireMsg (int, QString, int)), this, SLOT (slotAcceptMessage(int, QString, int))   );




    return 0 ;

    }

    int DeviceManagerIzluchatel::initList()
    {

        //в будущем будет инитить хеш устройств из xml файла
        //пока, для дебага, будем здесь добавлять разные устройства

        return 0;


    }


void DeviceManagerIzluchatel::setStandID(QString id)
{
currentstandid=id;
}


QString DeviceManagerIzluchatel::getStandID()
{
return currentstandid;
}



void DeviceManagerIzluchatel::slotAcceptMessage(int id, QString msg, int type)
    {
        /*
            here specifies where the message to go after reached this..
        */
        UI->acceptMessage(msg, id, type);
    }

void DeviceManagerIzluchatel::slotAcceptMeausure(int id, double value, QString type)
    {

UI->acceptMessage(tr ("Accepted measurement data: id = %1, value=%2 %3, type=%4").arg(QString::number(id)).arg(QString::number(value)).arg(type.toInt()?"дБ":"дБм").arg(type) ,id,MSG_NEUTRAL );
emit fireTransitMeasData(id,  value, type);
//передаём далее сигналом как пришло
//реализуется цепочка событий через сигнал-слот
    }


void DeviceManagerIzluchatel::slotAcceptDeviceConnected(int id)
    {
        UI->acceptPing(id);


        /*
            ещё бы что сделать здесь...
        */

    }



    void DeviceManagerIzluchatel::slotAcceptDeviceDisconnected(int id)
    {
        UI->displayDevices();
        UI->acceptMessage("Ошибка подключения - устройство недоступно", id,  MSG_ERROR);


        //транзитом передаём в principal, чтоб оно тестирование остановило, или ещё что там
        emit fireDeviceDisconnected(id);



    }
