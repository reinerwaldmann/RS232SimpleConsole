#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "DeviceManagerIzluchatel/devicemanagerizluchatel.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DeviceManagerIzluchatel * dvman;


private slots:
    void on_ControllerSet_clicked();


private:
    Ui::MainWindow *ui;

    void closeEvent(QCloseEvent *ce);
};

#endif // MAINWINDOW_H
