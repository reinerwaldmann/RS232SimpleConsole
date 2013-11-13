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
    ms(tr ("Port %1 successfully opened").arg (portname), MSG_DEBUG);
    }
    else
    {
    ms(tr ("ERR 2632 Port %1 error while opening").arg (portname), MSG_ERROR);
    return 2632;
    }


return 0;

    //return ping();

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
     //measurement is a ping, actually


     QTimer::singleShot(3000, this, SLOT(onPingFired()));


}

int DeviceRS232Rubin201::firePingAccepted()
{
    fireConnected();

    devman->acceptPing(id);
}


void DeviceRS232Rubin201::onDataAvailable()
{
//вся хрень шоб работало
        QByteArray qb = port->readAll();


        //displaying everything came to console
        QString txt = "<";


               for (int i=0; i<qb.size(); i++)
               {
                   txt.append(QString(" 0x").append( QString::number(qb.at(i),16 )).append("\n") );

               }

            //

        for (int i=0; i<qb.size(); i++)
        {
            buffer.append (qb.at(i));

            if (qb.at(i)==0xffffffffffffff82) //пришла команда на измерение
            {
                buffer.clear();
                buffer.append(0xffffffffffffff82);
            }



        }

        if ( (buffer.size()>2)&& (buffer.at(0)==0xffffffffffffff82)  ) //можно пробовать нечто интерпретировать
        {
            firePingAccepted();
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
    if (!isConnected)
        {
            ms("ERR 2651 Not connected",MSG_ERROR);
            return 2691;
        }



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
    /*if (!isConnected)
    {
        ms("ERR 2691 Not connected",MSG_ERROR);
        return 2691;
    }

    */


    //for debugging purposes set only for measurements!!!!!

        char sht=0x82;
        buffer.clear();

        if (msg.isEmpty())
     {
            ms("ERR 2692 Nothing to send",MSG_ERROR);
            return 2692;
     }
        char f [2];
        f[0] = (char) msg.toInt(0,16);



        f[1]='\0';
        port->write(f);
        ms(QString (">")+msg, MSG_DEBUG);

}

/*

*/



int DeviceRS232Rubin201::sendToPortMeasureValue()
{
    char sht=0x82;
    buffer.clear();
    char f [2];
    f[0] = sht;
    f[1]='\0';
    port->write(f);
    ms(QString (">")+QString::number(0x82), MSG_DEBUG);
}

QString DeviceRS232Rubin201::getPosition()
{
    return portname;

}


void  DeviceRS232Rubin201::onPingFired ()
{
    sendToPort("0x82");

}
