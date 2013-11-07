#include "devicewidget.h"
#include "ui_devicewidget.h"


//may be deprecated if table view will be used
DeviceWidget::DeviceWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceWidget)
{
    ui->setupUi(this);
}

DeviceWidget::~DeviceWidget()
{
    delete ui;
}
