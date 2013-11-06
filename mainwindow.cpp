#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboChooseBaud->addItem("9600", QVariant (9600));


    //buddys and shortcuts
    ui->labelChooseBaud->setBuddy(ui->comboChooseBaud);
    ui->labelCoosePort->setBuddy(ui->comboChoosePort);
    QShortcut *shortcut = new QShortcut(QKeySequence(Qt::Key_Return), this);
    QObject::connect(shortcut, SIGNAL(activated()), this, SLOT(on_pushSend_clicked()));


    portSettings.BaudRate=BAUD9600;
    portSettings.FlowControl=FLOW_OFF;
    portSettings.Parity=PAR_NONE;
    portSettings.DataBits=DATA_8;
    portSettings.StopBits=STOP_1;
    portSettings.Timeout_Millisec=600;
    port = new QextSerialPort(portSettings);


        displayActivePorts();


     connect(port, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
     buffer.clear();



     //debugging script
     ui->comboChoosePort->setCurrentIndex(1);
     ui->lineEnterValue->setText("0x82");
     on_pushConnect_clicked();

/*
     QTimer   * debug_timer  = new QTimer (this) ;
connect(debug_timer, SIGNAL(timeout()), this, SLOT(on_pushSend_clicked()));
debug_timer->start(1000);

*/

     //on_pushSend_clicked();



}

MainWindow::~MainWindow()
{
    disconnectx();
    port->close();
    delete port;
    delete ui;
}


void MainWindow::displayActivePorts()
{
    QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();

    char i(0);
      foreach( QextPortInfo port, ports ) {



          #ifdef Q_OS_WIN32
          if (port.portName.contains("COM"))
          #endif

          ui->comboChoosePort->addItem(port.portName,i++);

      }

}

void MainWindow::send ()
{
    buffer.clear();
    QString txt = ui->lineEnterValue->text();
    if (txt.isEmpty())
    {
        ms("Nothing to send",MSG_ERROR);
        return;

    }

    //ui->lineEnterValue->clear();

    char f [1];
    f[0] = (char) txt.toInt(0,16);
port->write( f );
ms(QString (">")+txt);


}

void MainWindow::connectx()
{
    port->setPortName(ui->comboChoosePort->currentText());
    if (port->open(QIODevice::ReadWrite | QIODevice::Unbuffered))
    {
        ms(tr ("Port %1 successfully opened").arg (ui->comboChoosePort->currentText()), MSG_GOOD );

    }
    else
    {

      ms(tr ("Port %1 error while opening").arg (ui->comboChoosePort->currentText()), MSG_ERROR);
    }


    ui->pushConnect->setEnabled(0);
    ui->pushDisconnect->setEnabled(1);
}


void MainWindow::disconnectx()
{

    ms(tr ("Port %1 successfully disconnected").arg (port->portName() ), MSG_GOOD );
    port->close();

    ui->pushConnect->setEnabled(1);
    ui->pushDisconnect->setEnabled(0);

}

void MainWindow::on_pushConnect_clicked()
{
connectx();
}

void MainWindow::on_pushDisconnect_clicked()
{
disconnectx();
}

void MainWindow::onDataAvailable()
{
//we'll make a parsing mechanizm only for measurement for now.

    QByteArray qb = port->readAll();

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
            //int t = buffer.at(1)<<8 + buffer.at(2);
            unsigned char high =  (unsigned char ) buffer.at(1);
            unsigned char low=  (unsigned char ) buffer.at(2);
            int  t = high;
            t= t <<8;
            t+=low;

            double result = t;
            result/=100;
            result*=buffer.at(3)?-1:1;

            ms ("result");
            ms (QString::number(result).append(buffer.at(4)?" дБ":" дБм") );
            ms ("\n\n");
            buffer.clear();
        }




  //  buffer.append(port->readAll());
/*    QString txt = "<";


    if (buffer.size()>7)
    {

        for (int i=0; i<buffer.size(); i++)
        {
            txt.append(QString(" 0x").append( QString::number(buffer.at(i),16 )).append("\n") );

        }


//0x82: произвести измерение, ответ 2б- измерения, 1б- знак,1б – (дБ/дБм), 2б-значение MRef*/
/*   char res = buffer.at(1)<<8 + buffer.at(2);
        txt.append(QString ("res = %1").arg(QString::number(res,16)));

        buffer.clear();

        ms(txt);
    }

*/

    //QString txt = "<";

      // QByteArray qb = port->readAll();

  /*  for (int i=0; i<qb.size(); i++)
    {
        txt.append(QString(" 0x").append( QString::number(qb.at(i),16 )));

//        if (qb.at(i)==0xffffffffffffff82) ms ("GG" ) ;



    }

*/
    //txt.append(QString (port->readAll())  );
   //ms(txt);


}

void MainWindow::on_pushSend_clicked()
{
    send();
}



void MainWindow::ms(QString message, char type)
{
    /*
#define MSG_ERROR 1
#define MSG_NEUTRAL 0
#define MSG_GOOD 2
*/

switch (type)
    {

    case MSG_ERROR:
        ui->textEditConsole->append(tr( "<font color=red> %1 </font>" ).arg(message) );
        break;
    case MSG_GOOD:
        ui->textEditConsole->append(tr( "<font color=green> %1 </font>" ).arg(message) );
        break;
    case MSG_NEUTRAL:
        ui->textEditConsole->append(tr( " %1" ).arg(message) );
        break;

    }

}

