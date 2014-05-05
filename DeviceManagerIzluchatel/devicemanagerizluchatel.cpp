#include "devicemanagerizluchatel.h"

DeviceManagerIzluchatel::DeviceManagerIzluchatel(PrincipalWindow * iprincipal, int icurrentstandid, QObject *parent):
    QObject(parent)
{
    //principal = dynamic_cast  <PrincipalWindow*> (parent);
    principal = iprincipal;
    controller = NULL;
    UI = new DeviceManagerIzluchatelUI (this);
    UI->show();

    currentstandid=icurrentstandid;

    slotAcceptMessage(0, tr("currentstandid=%1").arg(currentstandid), MSG_NEUTRAL);


    //для дебага
    //initActiveDeviceList(" ");

    char err (0);
    if (initList(tr("devsettings_%1.xml").arg(currentstandid))) //если попытки инициализровать список так не увенчались успехом
    {

        //инитим список активных
        if (initActiveDeviceList(" "))
        {

            slotAcceptMessage(0, tr("Фатальная ошибка %1 - отсутствуют данные об устройствах в стенде").arg(err), MSG_ERROR);
        }

    }


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
 *
 **/

     if (!devicesHash.contains(id)) {
         slotAcceptMessage(0, "measure Попытка запросить измерений у отсутствующего в списке устройств устройства", MSG_ERROR);
         return 1;
     }

     Measurer*  m =  dynamic_cast<Measurer*>(devicesHash.value(id));
    if (m==NULL)
    {
        slotAcceptMessage(0, "measure Попытка произвести измерения устройством, для этого не предназначенным", MSG_ERROR);
        return 2;
    }
    return  m->measure(type);

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

        //реализуем добавление из xml файла


        //добавление контроллера
        /*
            В настоящей версии контроллер добавляется по умолчанию (с параметрами по умолчанию),
            попытка подключиться к нему следует сразу.
            В дальнейшем, эту секцию можно будет развить - сделать так, чтобы процесс добавления контроллера можно было
            настраивать файлом требований к устройствам. Пока контроллер в файл включать не требуется, ибо включается по умолчанию.
            В редакции функции initActiveDeviceList(...) надлежит при обнаружении Jerome ноду с оным пропускать безо внимания,
            во избежание двойного включения.

        */

        int controllerid=1;
        DeviceLANJerome * djrm = new DeviceLANJerome ();
        addDevice(djrm,1, controllerid);
        connectALL(); //Этот вызов - для тех, кто добавлен принудительно, как контроллер.

        if (ifilename.isEmpty())
        {
            return 1;
        }


        QFile  infile (ifilename);

        if (!infile.open(QIODevice::ReadOnly | QIODevice::Text) )

        {
            slotAcceptMessage(0, "initlist Unable to open file with devices settings - probably new configuration applied", MSG_DEBUG);
            return 2;
        }
            QDomDocument doc;

            //QDomDocument doc("mydocument");
            if (!doc.setContent(&infile))
            {
              slotAcceptMessage(0, "initlist Error while setting content of the domdocument", MSG_ERROR);
                return 3 ;

            }


                QDomElement docElem = doc.documentElement();

                    //QString rootTag = docElem.tagName(); // берёт корневой тег
                //по состоянию на 18FEB2014 корневой main_part, но это изменится!


                //берём список элементов с тегом device
                QDomNodeList nodeList = docElem.elementsByTagName("device");

                for (int i=0; i<nodeList.size(); i++)

//                foreach (QDomNode node, nodeList)
                {

                    QDomNode node = nodeList.at(i);
                    //начинаем магию конфигурирования списка устройств
                    //ВНИМАНИЕ! не активных, а просто устройств, уже найденных
                    //подразумевается, что в файле устройства, которые на своих местах


                       QDomElement el = node.toElement();
                       int nodeid = el.attribute("id", "0").toInt();

                       int nodetype = el.attribute("type", "0").toInt();

                       int nodeuniquetype = el.attribute("unique_type", "0").toInt();


                       if (!nodeid)
                       {
                           slotAcceptMessage( 0, "Error in XML: no id", MSG_ERROR);
                           continue;

                       }

                       if (!nodetype)
                       {
                           slotAcceptMessage( 0, "Error in XML: no type", MSG_ERROR);
                           continue;

                       }

                       if (!nodeuniquetype)
                       {
                           slotAcceptMessage( 0, "Error in XML: no uniquetype", MSG_ERROR);
                           continue;

                       }

                       Device * dev;

                       switch (nodeuniquetype)
                       {
                        case 101:
                           dev = new DeviceRS232Rubin201 ();
                           dev->setID(nodeid);
                           dev->configureViaXml (node.toElement());

                           break;


                       default:


                       break;
                       }


                        addDevice(dev,1,nodeid);


                }


                       connectALL();




        return 0;


    }



int DeviceManagerIzluchatel::initActiveDeviceList(QString ifilename)
    {
/*Устройств с id=0 НЕ ДОЛЖНО БЫТЬ, так как идеологически это сам менеджер устройств (сообщения с таким айдишником на слот приёма
сообщений приходят только от него*/

/*Данная функция отрабатывает, если обнаружен файл с описанием требований к устройствам.
 *Ей должно имя файла передаваться параметром.
 * Есть мнение, что файл может выглядеть так же, как и снимок состояния устройств, только без состояний (с пустыми нодами)
*/

    /*В редакции функции initActiveDeviceList(...) надлежит при обнаружении Jerome ноду с оным пропускать безо внимания,
    во избежание двойного включения.
*/
    activeDevicesHash.clear();



    int readid=11; //типа мы так в файле прочитали - идентификатор устройства в пределах стенда 11 - потому что первая десятка служебная (??)
    DeviceRS232Rubin201 * rdev = new DeviceRS232Rubin201 (); //конструируем
    addDevice(rdev, 0, readid); //добавляем в список активных - вторая переменная как раз и символизирует об этом



    return 0;
    }

void DeviceManagerIzluchatel::setStandID(int id)
{
currentstandid=id;
}


int DeviceManagerIzluchatel::getStandID()
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
            UI->displayActiveDevices();

            if (activeDevicesHash.isEmpty()) savePositionsOftheDevices(tr("devsettings_%1.xml").arg(currentstandid));

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
        /// эту строчку СНЕСТИ, если требуетcя использовать другие порты, от MOXA отличные
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
        case 101: //RUBIN 201
 dynamic_cast <DeviceRS232Rubin201*> ( activeDevicesHash.value(idInActiveDevList) )->supersearch(selectedports);
        break;

        default:
            slotAcceptMessage(0, tr ("search RS232DevicesOnPorts - no port search method stated for this device= %1").arg(idInActiveDevList), MSG_ERROR);
            return 2;
        break;

        }


return 0;

}


int DeviceManagerIzluchatel::savePositionsOftheDevices (QString ifilename)
{


//    QDomDocument doc (tr ("DevicesSettings_%1").arg(currentstandid));

    QDomDocument doc;


    //doc.appendChild(QDomText ());

    /*QDomText txxt = doc.createTextNode("service_part");
    doc.appendChild(txxt);
*/



    QDomElement main_part = doc.createElement("main_part");
   doc.appendChild(main_part);

    foreach (Device * dev, devicesHash)
    {
        main_part.appendChild(dev->getXMLPOsition(&doc));

    }



      QFile file(ifilename);

      if (!file.open(QIODevice::WriteOnly))
      {

          slotAcceptMessage(0, "Unable to save XML settings", MSG_ERROR);
          return 1;

      }

  /*    QXmlStreamWriter xmlWriter(&file);
       xmlWriter.setAutoFormatting(true);
       xmlWriter.writeStartDocument();
*/
       //xmlWriter.write
      QTextStream  stream (&file);
      stream << doc.toString(10);

    stream.flush();
    file.close();

    return 0;

}


int DeviceManagerIzluchatel::wrLine(int numline, bool state)
{
//упрощённая версия, полагающая, что контроллер задан в переменной Controller
//здесь можно понаписать код, который будет искать контроллер в списке и инициализировать оную переменную
controller->wrLine(numline, state);
}
