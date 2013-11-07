#include "devicemanagerizluchatelui.h"
#include "ui_devicemanagerizluchatelui.h"

DeviceManagerIzluchatelUI::DeviceManagerIzluchatelUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceManagerIzluchatelUI)
{
    ui->setupUi(this);
}

DeviceManagerIzluchatelUI::~DeviceManagerIzluchatelUI()
{
    delete ui;
}
