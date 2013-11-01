#include "mainwindow.h"
#include "ui_mainwindow.h"


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

}

MainWindow::~MainWindow()
{
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
    QString txt = ui->lineEnterValue->text();
    if (txt.isEmpty())
    {
        ms("Nothing to send",MSG_ERROR);
        return;

    }

    ui->lineEnterValue->clear();

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

    QString txt = "<";

       QByteArray qb = port->readAll();

    for (int i=0; i<qb.size(); i++)
    {
        txt.append(QString(" 0x").append( QString::number(qb.at(i),16 )));


    }


    //txt.append(QString (port->readAll())  );
    ms(txt);


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

