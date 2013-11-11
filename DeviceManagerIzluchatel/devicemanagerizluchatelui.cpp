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
            ui->console->append(tr( "<font color=red> %1 </font>" ).arg(msg) );
            break;
        case MSG_GOOD:
            ui->console->append(tr( "<font color=green> %1 </font>" ).arg(msg) );
            break;
        case MSG_NEUTRAL:
            ui->console->append(tr( " %1" ).arg(msg) );
            break;
        case MSG_DEBUG: //yet debug flag not implemented
            ui->console->append(tr( " %1" ).arg(msg) );
            break;
        }
}


void DeviceManagerIzluchatelUI::acceptPing(int id)
{
    ui->console->append(tr( "<font color=green> %1 %2 </font>" ).arg("ACCEPTED PING FROM").arg(QString::number(id)) );

}


void DeviceManagerIzluchatelUI::displayDevices()
{
    QList <char> keylist = devman->devicesHash.keys();

    ui->tableWidget->clear();

    ui->tableWidget->setRowCount(keylist.size());
    ui->tableWidget->setColumnCount(5);

    char k;
    foreach (k, keylist)
    {
       QTableWidgetItem * item = new QTableWidgetItem (QString::number (k));
       QTableWidgetItem * item1 = new QTableWidgetItem (devman->devicesHash.value(k)->name );
       QTableWidgetItem * item2 = new QTableWidgetItem (devman->devicesHash.value(k)->isConnected?"Connected":"Disconnected");
       QTableWidgetItem * item3 = new QTableWidgetItem (devman->devicesHash.value(k)->getPosition());



       item->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
       item1->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
       item2->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);
       item3->setFlags(Qt::NoItemFlags|Qt::ItemIsSelectable|Qt::ItemIsEnabled);


       ui->tableWidget->setItem(k,0,item);
       ui->tableWidget->setItem(k,1,item1);
       ui->tableWidget->setItem(k,2,item2);
       ui->tableWidget->setItem(k,3,item3);

      ui->tableWidget->setIndexWidget(ui->tableWidget->model()->index(k,4), new QPushButton);


    }


}
