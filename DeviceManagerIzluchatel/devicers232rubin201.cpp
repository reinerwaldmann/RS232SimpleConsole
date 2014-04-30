#include "devicers232rubin201.h"

DeviceRS232Rubin201::DeviceRS232Rubin201()
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
    timeout=2000;


    waitingForConnect=0;

    uniqueType=101;

}

DeviceRS232Rubin201::~DeviceRS232Rubin201 ()
{}


void DeviceRS232Rubin201::onDataAvailable()
{
        reqtimer->stop();
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
            if (waitingForConnect)
            {
             setConnectedState(1);
             //waitingForConnect=0; //при этом закомментированном начинает работать нормально!
             return;
            }




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

            //devman->acceptMeausure(result, id, buffer.at(4));




            fireMeasurementData(id,result, QString::number(buffer.at(4)));


            //1 - dB    0 - dBm - that's about last parameter


            buffer.clear();




        }




}

int  DeviceRS232Rubin201::measure(QString type)
{
//запущает  процесс измерений

    //for debugging
//    qDebug ("MEASURE STARTED DEVICE RUBIN");


    waitingForConnect=0;

    if (!isConnected)
        {
            emit fireDisconnected(id);
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

        reqtimer->start(timeout);
}


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


void  DeviceRS232Rubin201::onPingFired ()
{
    sendToPort("0x82");

}

int DeviceRS232Rubin201::ping()     //measurement is a ping, actually
{
      QTimer::singleShot(3000, this, SLOT(onPingFired()));

      waitingForConnect=1;

        return 0;



}


QDomElement DeviceRS232Rubin201::getXMLPOsition(QDomDocument * idoc)
{

   /* QDomElement node ();
    node.setTagName("device");
    node.setAttribute("id", id );
    node.setAttribute("unique_type", uniqueType);
    node.setAttribute("type", type);
*/

    QDomElement node = Device::getXMLPOsition(idoc);



    QDomElement val = idoc->createElement("portname");


    QDomText txt = idoc->createTextNode(port->portName()) ;
    //txt.setData(port->portName());
//    txt.setNodeValue(port->portName());

    val.appendChild(txt);
    node.appendChild(val);




    return node;






}
