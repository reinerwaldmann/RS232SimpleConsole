#include "devicefinder.h"
#include "ui_devicefinder.h"

DeviceFinder::DeviceFinder(DeviceManagerIzluchatel *idevman, QWidget *parent):
    QDialog(parent),
    ui(new Ui::DeviceFinder)
{
    ui->setupUi(this);

    devman = idevman;

  outAllSerialPorts();

}

DeviceFinder::~DeviceFinder()
{
    delete ui;
}


void DeviceFinder::outAllSerialPorts () //outputs all ports  to the console and writes them to the list
{

    //отображение доступных RS232 портов

    selectedports.clear();
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
    con ("enumName \t friendName \t physName \t portName" );

       foreach (QextPortInfo port, ports) {
           // inspect port...
       //мы фильтруем порты, чтоб отобрать только те, которые относятся к MOXA
    /// эту строчку СНЕСТИ, если требуестя использовать другие порты, от MOXA отличные
           //возможно, лучше внести опцию работы с отличными от MOXA разветвителями в настройки
           if (!port.friendName.contains("MOXA")) continue;
           con (tr ("%1 \t %2 \t %3 \t %4").arg(port.enumName).arg(port.friendName).arg(port.physName).arg(port.portName) );
           selectedports.append(port);

       }



}
void DeviceFinder::con (QString msg) //appends text to console
{
    ui->textEditConsole->append(msg);

}

