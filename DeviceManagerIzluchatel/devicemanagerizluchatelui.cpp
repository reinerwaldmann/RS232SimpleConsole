#include "devicemanagerizluchatelui.h"
#include "ui_devicemanagerizluchatelui.h"

DeviceManagerIzluchatelUI::DeviceManagerIzluchatelUI(DeviceManagerIzluchatel *idevman, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceManagerIzluchatelUI)
{
    ui->setupUi(this);
    devman = idevman;
    ui->comboLevelOfOutput->setCurrentIndex(2);
    ui->searchDevice_2->hide();

}

DeviceManagerIzluchatelUI::~DeviceManagerIzluchatelUI()
{
    delete ui;
}


void DeviceManagerIzluchatelUI::acceptMessage(QString msg, int id, int type)
{

    char level = ui->comboLevelOfOutput->currentIndex();

    switch (type)
        {

        case MSG_ERROR:
            ui->console->append(tr( "<font color=red> ID=%1  %2 </font>" ).arg(QString::number(id)).arg(msg) );
            break;
        case MSG_GOOD:
            if (level)
            ui->console->append(tr( "<font color=green> ID=%1 %2 </font>" ).arg(QString::number(id)).arg(msg) );
            break;
        case MSG_NEUTRAL:
            if (level)
            ui->console->append(tr( "ID=%1 %2" ).arg(QString::number(id)).arg(msg) );
            break;
        case MSG_DEBUG: //yet debug flag not implemented
            if (level>1)
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
    if (devman->activeDevicesHash.empty())
     {ui->searchDevice->setEnabled(0); }
    else
     {ui->searchDevice->setEnabled(1); }



    QList <int> keylist = devman->devicesHash.keys();



    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(keylist.size());
    ui->tableWidget->setColumnCount(5);


    QStringList l;
    l<<"Идентификатор"<<"Имя устройства"<<"Состояние"<<"Порт"<<"Проверить связь/Измерить";
    ui->tableWidget->setHorizontalHeaderLabels(l);

    int k, r(0);
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




       ui->tableWidget->setItem(r,0,item);
       ui->tableWidget->setItem(r,1,item1);
       ui->tableWidget->setItem(r,2,item2);
       ui->tableWidget->setItem(r,3,item3);

       QPushButton * conButton = new QPushButton ("Проверить связь");

       connect (conButton, SIGNAL (clicked()),devman->devicesHash.value(k), SLOT(slotConnectx()) );
       ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(r,4), conButton);
       r++;

    }


    ui->tableWidget->resizeColumnsToContents();


}

void DeviceManagerIzluchatelUI::on_searchDevice_clicked()
{
devman->searchRS232DevicesOnPorts( ui->comboListOfDevices->itemData(ui->comboListOfDevices->currentIndex()).toInt()  );
}

void DeviceManagerIzluchatelUI::displayActiveDevices()
{
    ui->comboListOfDevices->clear();
    ui->searchDevice->setEnabled(!devman->activeDevicesHash.isEmpty());
    foreach (Device * dev, devman->activeDevicesHash)
    {
        //в списке активных те же идентификаторы, какие будут и в списке устройств
        ui->comboListOfDevices->addItem( dev->getName()+" ID="+QString::number(dev->getID()), dev->getID());
    }

}



void DeviceManagerIzluchatelUI::on_searchDevice_2_clicked()
{

}
