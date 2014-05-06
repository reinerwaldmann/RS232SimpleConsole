#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    dvman = new DeviceManagerIzluchatel (1803, this);


    ui->setupUi(this);
    ui->standNumber->setText("1803");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ControllerSet_clicked()
{

}
