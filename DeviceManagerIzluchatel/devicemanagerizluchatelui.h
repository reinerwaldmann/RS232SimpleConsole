#ifndef DEVICEMANAGERIZLUCHATELUI_H
#define DEVICEMANAGERIZLUCHATELUI_H

#include <QWidget>
#include "devicemanagerizluchatel.h"
#include <QPushButton>


#include<QDebug>

#define MSG_ERROR 1
#define MSG_NEUTRAL 0
#define MSG_GOOD 2
#define MSG_DEBUG 3

class  DeviceManagerIzluchatel;

namespace Ui {
class DeviceManagerIzluchatelUI;
}

class DeviceManagerIzluchatelUI : public QWidget
{
    Q_OBJECT
    
public:
    explicit DeviceManagerIzluchatelUI(DeviceManagerIzluchatel * idevman, QWidget *parent = 0);
    ~DeviceManagerIzluchatelUI();
    
    void acceptMessage (QString msg, int id, int type);

    void acceptPing(int id);


    /*
     *A way of displaying the devices  and what is going on with them
    */
    void displayDevices();
    void displayActiveDevices();




    DeviceManagerIzluchatel * devman;

private slots:
    void on_searchDevice_clicked();

    void on_searchDevice_2_clicked();

private:
    Ui::DeviceManagerIzluchatelUI *ui;
};

#endif // DEVICEMANAGERIZLUCHATELUI_H
