#include "devicers232.h"

DeviceRS232::DeviceRS232()
{
type=1; //RS232

descr="RS232 device";

timeout=2000;
}


DeviceRS232::~DeviceRS232()
{}

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
    if (!portname.length())
    {
        ms(tr ("ERR DeviceRS232 no portname specified"), MSG_ERROR);

        return 1;
    }

    //port->setPortName(portname);
    if (port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
    {
    ms(tr ("MSG DeviceRS232 Port %1 successfully opened").arg (portname), MSG_DEBUG);
    }
    else
    {
    ms(tr ("ERR DeviceRS232 Port %1 error while opening").arg (portname), MSG_ERROR);
    return 2;
    }
    return ping();
}


int DeviceRS232::disconnecx()
{
port->close();
setConnectedState(0);
}
