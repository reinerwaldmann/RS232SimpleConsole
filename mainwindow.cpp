#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSpinBox>
#include <QCheckBox>
#include <QPlainTextEdit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    dvman = new DeviceManagerIzluchatel (1803);


    ui->setupUi(this);
    ui->standNumber->setText("1803");





}

MainWindow::~MainWindow()
{
    //delete dvman;
    delete ui;
}

void MainWindow::on_ControllerSet_clicked()
{

    if (dvman->checkAllOK()==0)//all devices OK, connected
    {
       //dvman->wrLine(,1);
        int numline = ui->lineNum->value();
        if (numline<10)

            ui->plainTextEdit->appendPlainText( dvman->wrLine(numline, ui->On->isChecked())?"Error":"OK");

        ui->plainTextEdit->appendPlainText(tr("line=%1 state=%2").arg(QString::number(numline)).arg(ui->On->isChecked()));

    }
    else
    {
        ui->plainTextEdit->appendPlainText("Error, not all devices connected");


    }

}


void MainWindow::closeEvent(QCloseEvent *ce)
{
dvman->UI->close();
}
