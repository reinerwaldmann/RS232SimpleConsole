#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qextserialport.h>
#include <qextserialenumerator.h>
#include <QShortcut>


#define MSG_ERROR 1
#define MSG_NEUTRAL 0
#define MSG_GOOD 2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void displayActivePorts();
    void send ();
    void connectx();
    void disconnectx();
    void ms(QString message, char type=0);

QextSerialPort *   port;
PortSettings portSettings;



    
private:
    Ui::MainWindow *ui;

private slots:
    void onDataAvailable();
    void on_pushConnect_clicked();
    void on_pushDisconnect_clicked();
    void on_pushSend_clicked();
};

#endif // MAINWINDOW_H