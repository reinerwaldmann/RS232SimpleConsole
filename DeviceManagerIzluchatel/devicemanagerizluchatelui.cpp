#include "devicemanagerizluchatelui.h"
#include "ui_devicemanagerizluchatelui.h"

DeviceManagerIzluchatelUI::DeviceManagerIzluchatelUI(DeviceManagerIzluchatel *idevman, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceManagerIzluchatelUI)
{
    ui->setupUi(this);
    devman = idevman;

}

DeviceManagerIzluchatelUI::~DeviceManagerIzluchatelUI()
{
    delete ui;
}


void DeviceManagerIzluchatelUI::acceptMessage(QString msg, int id, int type)
{
    switch (type)
        {

        case MSG_ERROR:
            ui->console->append(tr( "<font color=red> ID=%1  %2 </font>" ).arg(QString::number(id)).arg(msg) );
            break;
        case MSG_GOOD:
            ui->console->append(tr( "<font color=green> ID=%1 %2 </font>" ).arg(QString::number(id)).arg(msg) );
            break;
        case MSG_NEUTRAL:
            ui->console->append(tr( "ID=%1 %2" ).arg(QString::number(id)).arg(msg) );
            break;
        case MSG_DEBUG: //yet debug flag not implemented
            ui->console->append(tr( "ID=%1 %2" ).arg(QString::number(id)).arg(msg) );
            break;
        }
}


void DeviceManagerIzluchatelUI::acceptPing(int id)
{
    ui->console->append(tr( "<font color=green> %1 %2 </font>" ).arg("ACCEPTED PING FROM").arg(QString::number(id)) );
    displayDevices(); // updating the devices state
}


void DeviceManagerIzluchatelUI::displayDevices()
{
    QList <char> keylist = devman->devicesHash.keys();

    ui->tableWidget->clear();

    ui->tableWidget->setRowCount(keylist.size());
    ui->tableWidget->setColumnCount(5);


    QStringList l;
    l<<"Идентификатор"<<"Имя устройства"<<"Состояние"<<"Порт"<<"Проверить связь/Измерить";
    ui->tableWidget->setHorizontalHeaderLabels(l);


    char k;
    foreach (k, keylist)
    {
       QTableWidgetItem * item = new QTableWidgetItem (QString::number (k));
       QTableWidgetItem * item1 = new QTableWidgetItem (devman->devicesHash.value(k)->getName());
       QTableWidgetItem * item2 = new QTableWidgetItem (devman->devicesHash.value(k)->getIsConnected()?"Подключено":"Отключено");
       QTableWidgetItem * item3 = new QTableWidgetItem (devman->devicesHash.value(k)->getPosition());



       item->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
       item1->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
       item2->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
       item3->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);


       ui->tableWidget->setItem(k,0,item);
       ui->tableWidget->setItem(k,1,item1);
       ui->tableWidget->setItem(k,2,item2);
       ui->tableWidget->setItem(k,3,item3);

       QPushButton * conButton = new QPushButton ("Проверить связь");

       connect (conButton, SIGNAL (clicked()),devman->devicesHash.value(k), SLOT(onPingFired()) );


       ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(k,4), conButton);


    }


    ui->tableWidget->resizeColumnsToContents();


}
