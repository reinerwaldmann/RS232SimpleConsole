#include "devicers232rubin201.h"

DeviceRS232Rubin201::DeviceRS232Rubin201(DeviceManagerIzluchatel *iman):
DeviceRS232 (iman)
{
    portSettings.BaudRate=BAUD9600;
    portSettings.FlowControl=FLOW_OFF;
    portSettings.Parity=PAR_NONE;
    portSettings.DataBits=DATA_8;
    portSettings.StopBits=STOP_1;
    portSettings.Timeout_Millisec=600;
    port = new QextSerialPort(portSettings);
connect(port, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));



}


DeviceRS232Rubin201::~DeviceRS232Rubin201 ()
{
    disconnecx();

}

void DeviceRS232Rubin201::setPort(QString iport)
{

portname = iport;


}

void DeviceRS232Rubin201::connectx()
{

if (!portname.length()) return;
port->setPortName(portname);

if (port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
{
fireConnected();
}
else
{
ms(tr ("Port %1 error while opening").arg (portname), id, MSG_ERROR);
}





}

void DeviceRS232Rubin201::fireConnected()
{
isConnected=1;
}

void DeviceRS232Rubin201::disconnecx()
{
port->close();
isConnected=0;
}

void DeviceRS232Rubin201::ping()
{}

void DeviceRS232Rubin201::firePingAccepted()
{

}




void DeviceRS232Rubin201::onDataAvailable()
{
//вся хрень шоб работало


}

void DeviceRS232Rubin201::measure(int type)
{
//запущает  процесс измерений

    //for debugging
    qDebug ("MEASURE STARTED DEVICE RUBIN");

}
