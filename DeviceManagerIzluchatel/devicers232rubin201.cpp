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

    name = "Рубин 201";
    descr = "Измеритель оптической мощности";


}

DeviceRS232Rubin201::~DeviceRS232Rubin201 ()
{
    disconnecx();
}

void DeviceRS232Rubin201::setPort(QString iport)
{
portname = iport;
}

int DeviceRS232Rubin201::connectx()
{

if (!portname.length())
{
ms(tr ("ERR 2631 no portname specified"), MSG_ERROR);
return 2631;
}



port->setPortName(portname);

if (port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
{
fireConnected();
}
else
{
ms(tr ("ERR 2632 Port %1 error while opening").arg (portname), MSG_ERROR);
}

}

int DeviceRS232Rubin201::fireConnected()
{
isConnected=1;
}

int DeviceRS232Rubin201::disconnecx()
{
port->close();
isConnected=0;
}

int DeviceRS232Rubin201::ping()
{
     measure(0); //measurement is a ping, actually
}

int DeviceRS232Rubin201::firePingAccepted()
{
    devman->acceptPing(id);
}


void DeviceRS232Rubin201::onDataAvailable()
{
//вся хрень шоб работало
        QByteArray qb = port->readAll();

        for (int i=0; i<qb.size(); i++)
        {
            buffer.append (qb.at(i));

            if (qb.at(i)==0xffffffffffffff82) //пришла команда на измерение
            {
                buffer.clear();
                buffer.append(0xffffffffffffff82);

                firePingAccepted();
            }


            if (qb.at(i)==0xffffffffffffff82) //пришла команда на измерение
            {
                buffer.clear();
                buffer.append(0xffffffffffffff82);
            }

        }

        if ( (buffer.size()>2)&& (buffer.at(0)==0xffffffffffffff82)  ) //можно пробовать нечто интерпретировать
        {
            //int t = buffer.at(1)<<8 + buffer.at(2);
            unsigned char high =  (unsigned char ) buffer.at(1);
            unsigned char low=  (unsigned char ) buffer.at(2);
            int  t = high;
            t= t <<8;
            t+=low;

            double result = t;
            result/=100;
            result*=buffer.at(3)?-1:1;

       /*     ms ("result");
            ms (QString::number(result).append(buffer.at(4)?" дБ":" дБм") );
            ms ("\n\n");
*/

            devman->acceptMeausure(result, id, buffer.at(4));
            //1 - dB    0 - dBm - that's about last parameter


            buffer.clear();




        }




}

int  DeviceRS232Rubin201::measure(int type)
{
//запущает  процесс измерений

    //for debugging
//    qDebug ("MEASURE STARTED DEVICE RUBIN");
    return sendToPort("0x82");

}

/**
 * @brief DeviceRS232Rubin201::sendToPort
 *transforms msg into a numerical value in base 16, then sends it to the port
 * @param msg
 * @return 1 if error, 0 if everything is OK
 */
int DeviceRS232Rubin201::sendToPort(QString msg)
//msg being transformed into a numerical value
{
    if (!isConnected)
    {
        ms("ERR 2691 Not connected",MSG_ERROR);
        return 2691;
    }
        buffer.clear();
        QString txt = msg;
        if (txt.isEmpty())
     {
            ms("ERR 2692 Nothing to send",MSG_ERROR);
            return 2692;
     }
        char f [1];
        f[0] = (char) txt.toInt(0,16);
        port->write(f);
        ms(QString (">")+txt, MSG_DEBUG);

}


QString DeviceRS232Rubin201::getPosition()
{
    return portname;

}
