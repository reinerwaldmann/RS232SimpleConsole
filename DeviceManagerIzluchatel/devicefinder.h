#ifndef DEVICEFINDER_H
#define DEVICEFINDER_H

#include <QDialog>
#include "qextserialenumerator.h"
#include "devicemanagerizluchatel.h"


class DeviceManagerIzluchatel;

namespace Ui {
class DeviceFinder;
}

class DeviceFinder : public QDialog
{
    Q_OBJECT
    
public:
    explicit DeviceFinder(DeviceManagerIzluchatel * idevman,  QWidget *parent = 0);
    ~DeviceFinder();

    void outAllSerialPorts (); //outputs all ports  to the console and writes them to the list
    void con (QString msg); //appends text to console





    QList<QextPortInfo> selectedports;  //RS232 порты в системе, которые мы будем рассматривать
    DeviceManagerIzluchatel *devman;
    QHash <char, Device * > outDevicesHash; //список устройств. Скармливается менеджеру устройств после завершения работы
    QList <Device * > inDevicesList; //список устройств на входе

    /*
        Алгоритм предельно прост - берём первое устройство из списка.
        Пробуем подключить его к любому порту

    */




private:
    Ui::DeviceFinder *ui;
};

#endif // DEVICEFINDER_H
