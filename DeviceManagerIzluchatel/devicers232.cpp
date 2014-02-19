#include "devicers232.h"

DeviceRS232::DeviceRS232()
{
type=1; //RS232
descr="RS232 device";
timeout=2000;
 }


DeviceRS232::~DeviceRS232()
{
    port->close();
}


int DeviceRS232::configureViaXml (QDomElement iel)
{
QDomNodeList nodeList = iel.elementsByTagName("portname");
if (nodeList.isEmpty())
{
    ms("Error: no portname section in XML", MSG_ERROR);
    return 1;
}

QString portnamex = nodeList.at(0).toElement().childNodes().at(0).toText().data();

ms (portnamex,MSG_DEBUG);

if (portnamex.isEmpty())
{
    ms("Error: portname section in XML is empty", MSG_ERROR);
    return 1;
}

port->setPortName(portnamex);


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


return 0;
}


void DeviceRS232::supersearch (QList<QextPortInfo> inlist)
{
    ms("Search_Started",MSG_DEBUG);
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
    ms(tr ("Search: idInSearchList=%1").arg(idInSearchList),MSG_DEBUG);


    if (idInSearchList>=searchPortLst.size())
    {
        //ругнулись на то, что найти не удалось
        ms(tr ("Найти устройство не вышло id=%1").arg(id), MSG_ERROR);
        emit fireDisconnected(id); //чтобы менеджер знал, что найти не удалось!
        portIsSearched=0;//сняли флаг поиска, так как поиск завершён, пусть и неудачей
     //   searchPortLst.clear(); //чтоб даже искать не пытался вдруг
        return;

    }


    //собственно, действия
    //устанавливаем порт
    port->setPortName(searchPortLst.at(idInSearchList).portName);


        ms(tr ("Search: portname=%1").arg(port->portName()),MSG_DEBUG);


        //если законнектиться не вышло, что может произойти в случае, если на порту уже есть какое-то устройство,
        //то надо продвигаться дальше по портам
    while (connectx()) {
        idInSearchList++;
        port->setPortName(searchPortLst.at(idInSearchList).portName);
    }

        //connectx();
     ms(tr ("Connect triggered"),MSG_DEBUG);


    //и мы пытаемся подключиться. Если подключиться получилось, то устройство
    //запустит слот fireConnected
    /*
        Дальше вопрос - либо сносить подключенный порт из списка и возвращать список, либо
        менеджер сам по пришествии сигнала от того девайса, который сейчас в активном поиске,
        выведет ошибку (если не нашёлся), а если нашёлся, то перед подачей списка другому устройству
        сам посносит оттуда порты подключенных устройств.

        УПРТСТЬ!!!!!!Ё!!!!Омск!!!!!


        Важный момент! до тех пор пока не случилось коннекта или дисконнекта, менеджер не
        должен разрешать поиск порта, не то конфликт и ужос. 13 портов тестятся 40 сек, не менее!



    */



}

void DeviceRS232::setConnectedState (bool isState)
{

    if (portIsSearched) //если мы ищем порт

    {
        if (!isState)  //, то дело лишь в том, что на  данном порту нет устройства

        {
            port->close(); //порт закрываем
            ms(tr ("setConnectedState triggered with 0 parameter, starting search"),MSG_DEBUG); //рассказываем, что таки нет устройства
            search (); // и запускаем поиск обратно, он сам уже начнёт другой порт опрашивать

        return; //вернуться из функции, чтоб левого ничего не запустить
        }


    }
    //теперь если порт не ищем

    //ms(tr ("nexxt"),MSG_DEBUG); //рассказываем, что таки нет устройства




    isConnected=isState;  //иначе присвариваем

    if (isConnected) //если наконец подключились
    {
        //if (isState!=isConnected)  //если состояние не такое, как пришло
       //{
            emit fireConnected(id); //рассказать, что подключились
            portIsSearched=0; //и отключить поиск порта,если он был включен
        //}
    }

   else //иначе, если мы отключены
    {
            emit fireDisconnected(id);//об этом надо рассказать
    }



    }










