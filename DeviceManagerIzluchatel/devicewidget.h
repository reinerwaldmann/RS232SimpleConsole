#ifndef DEVICEWIDGET_H
#define DEVICEWIDGET_H

#include <QWidget>

namespace Ui {
class DeviceWidget;
}

class DeviceWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit DeviceWidget(QWidget *parent = 0);
    ~DeviceWidget();
    
private:
    Ui::DeviceWidget *ui;
};

#endif // DEVICEWIDGET_H
