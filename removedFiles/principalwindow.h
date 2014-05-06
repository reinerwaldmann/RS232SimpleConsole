#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qextserialport.h>
#include <qextserialenumerator.h>
#include <QShortcut>
#include "DeviceManagerIzluchatel/devicemanagerizluchatel.h"
#include "DeviceManagerIzluchatel/devicers232rubin201.h"





#define MSG_ERROR 1
#define MSG_NEUTRAL 0
#define MSG_GOOD 2
#define MSG_DEBUG 3


class DeviceManagerIzluchatel;

namespace Ui {
class MainWindow;
}

class PrincipalWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PrincipalWindow(QWidget *parent = 0);
    ~PrincipalWindow();
    void displayActivePorts();
    void send ();
    void connectx();
    void disconnectx();
    void ms(QString message, char type=0);

QextSerialPort *   port;
PortSettings portSettings;

QByteArray buffer;


DeviceManagerIzluchatel * dvm;




    
private:
    Ui::MainWindow *ui;

private slots:
    void onDataAvailable();
    void on_pushConnect_clicked();
    void on_pushDisconnect_clicked();
    void on_pushSend_clicked();

    void slotTestDeviceManager(int id, double value, QString type);
    void slotDeviceManagerDeviceDisconnected(int id);

};

#endif // MAINWINDOW_H
