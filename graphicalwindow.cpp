#include "graphicalwindow.h"
#include "ui_graphicalwindow.h"

GraphicalWindow::GraphicalWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphicalWindow)
{
    ui->setupUi(this);
}

GraphicalWindow::~GraphicalWindow()
{
    delete ui;
}
