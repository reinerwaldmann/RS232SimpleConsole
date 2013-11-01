#include "graphicalwidget.h"
#include "ui_graphicalwidget.h"

GraphicalWidget::GraphicalWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicalWidget)
{
    ui->setupUi(this);
}

GraphicalWidget::~GraphicalWidget()
{
    delete ui;
}
