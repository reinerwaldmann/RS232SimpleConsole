#include "devicemanagerizluchatel.h"

DeviceManagerIzluchatel::DeviceManagerIzluchatel(PrincipalWindow *iprincipal, QObject *parent):
    QObject(parent)
{
    principal = dynamic_cast  <PrincipalWindow*> (parent);
    UI = new DeviceManagerIzluchatelUI (this);
    UI->show();


    //для дебага
    initActiveDeviceList(" ");




}


DeviceManagerIzluchatel::~DeviceManagerIzluchatel ()
{




        QList <int> keylist = devicesHash.keys();
        char key;
        foreach (key, keylist)
        {
            //devicesHash.value(key)->disconnecx(); //оно само дисконнектит в деструкторах
            delete devicesHash.value(key);
        }

    devicesHash.clear();
    activeDevicesHash.clear();




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

     if (!devicesHash.contains(id)) {
         slotAcceptMessage(0, "measure Попытка запросить измерений у отсутствующего в списке устройств устройства", MSG_ERROR);
         return 1;
     }
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

    /**
     * @brief DeviceManagerIzluchatel::addDevice
     * @param idevice
     * @param where 0 - to the active devices 1 - to the devices
     * @param desiredid
     * @return
     */
    int DeviceManagerIzluchatel::addDevice(Device *idevice, bool where,  int desiredid)
    {
        //where - 0 - в список активных устройств, 1 в список просто устройствs

        int newid = desiredid;

        if (!desiredid)
        {
            newid=devicesHash.keys().length()+1;
        }


        idevice->setID(newid);

        if (where)
        {
        devicesHash.insert(newid, idevice);
        UI->displayDevices(); //прямой вызов к интерфейсу, может быть заменён на связь сигнал-слот
        }
         else
        {
        activeDevicesHash.insert(newid, idevice);
        UI->displayActiveDevices();
        }



        connect (idevice, SIGNAL (fireConnected (int)), this, SLOT (slotAcceptDeviceConnected(int))  );
        connect (idevice, SIGNAL (fireDisconnected (int)), this, SLOT (slotAcceptDeviceDisconnected(int))  );
        connect (idevice, SIGNAL (fireMeasurementData (int, double, QString)), this, SLOT (slotAcceptMeausure(int,double, QString))  );
        connect (idevice, SIGNAL (fireMsg (int, QString, int)), this, SLOT (slotAcceptMessage(int, QString, int))   );




    return 0 ;

    }

    int DeviceManagerIzluchatel::initList(QString ifilename)
    {

        devicesHash.clear();
        //в будущем будет инитить хеш устройств из xml файла
        //пока, для дебага, будем здесь добавлять разные устройства

        return 0;


    }



int DeviceManagerIzluchatel::initActiveDeviceList(QString ifilename)
    {


/*Данная функция отрабатывает, если обнаружен файл с описанием требований к устройствам.
 *Ей должно имя файла передаваться параметром.
*/

    activeDevicesHash.clear();
    int readid=1; //типа мы так в файле прочитали
    DeviceRS232Rubin201 * rdev = new DeviceRS232Rubin201 (); //конструируем

    addDevice(rdev, 0, readid); //добавляем в список активных

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
        //так как эта функция вызывается после поиска устройств на портах, то делаем вот что:
        if (activeDevicesHash.contains(id)) //если список активных содержит этот идентификатор
        {
            addDevice(activeDevicesHash.value(id), 1, id); //добавляем устройство в список найденных  устройств
            activeDevicesHash.remove(id); //сносим устройство из списка активных устройств
         }


    }



    void DeviceManagerIzluchatel::slotAcceptDeviceDisconnected(int id)
    {
        UI->displayDevices();
        UI->acceptMessage("Ошибка подключения - устройство недоступно", id,  MSG_ERROR);


        //транзитом передаём в principal, чтоб оно тестирование остановило, или ещё что там
        emit fireDeviceDisconnected(id);



    }


int DeviceManagerIzluchatel::searchRS232DevicesOnPorts  (int idInActiveDevList)
{


    //получение списка доступных RS232 портов

    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    QList<QextPortInfo> selectedports;
    slotAcceptMessage(0,"searchRS232DevicesOnPOrts triggered, alpha version DEBUG",MSG_DEBUG);
    slotAcceptMessage(0,"enumName \t friendName \t physName \t portName",MSG_DEBUG);

    foreach (QextPortInfo port, ports) {

       //мы фильтруем порты, чтоб отобрать только те, которые относятся к MOXA
        /// эту строчку СНЕСТИ, если требуестя использовать другие порты, от MOXA отличные
        //Эта часть не является универсальной и годна только для исполнения работы с MOXA
        //возможно, лучше внести опцию работы с отличными от MOXA разветвителями в настройки
           if (!port.friendName.contains("MOXA"))
           {
               continue;
           }


           //рассказываем  о найденном в консоли
           slotAcceptMessage(0, tr ("%1 \t %2 \t %3 \t %4").arg(port.enumName).arg(port.friendName).arg(port.physName).arg(port.portName), MSG_DEBUG );
           selectedports.append(port);
       }



    //если айди не обнаружен в списке активных устройств
    if (!activeDevicesHash.contains(idInActiveDevList))
    {
        slotAcceptMessage(0, tr ("search RS232DevicesOnPorts - no such device in active devices list id = %1").arg(idInActiveDevList), MSG_ERROR);
        return 1;
    }






    //костыль для того, чтоб нормально приводить к типам.
    //дело в том, что, хотя большая часть функций по поиску реализована в DeviceRS232, некоторые функции
    //типа  ping и т. п. имеют реализацию только в дочерних классах.
    //уйти от этого универсализацией не получается. Потому используется пока такой способ. Вряд ли он верный, но что поделать
    //14FEB2014
    switch (activeDevicesHash.value(idInActiveDevList)->getUniqueType())
        {
        case 1: //RUBIN 201
 dynamic_cast <DeviceRS232Rubin201*> ( activeDevicesHash.value(idInActiveDevList) )->supersearch(selectedports);
        break;

        default:
            slotAcceptMessage(0, tr ("search RS232DevicesOnPorts - no port search method stated for this device= %1").arg(idInActiveDevList), MSG_ERROR);
            return 2;
        break;

        }



}
