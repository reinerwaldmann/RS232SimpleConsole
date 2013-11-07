#ifndef DEVICEMANAGERIZLUCHATELUI_H
#define DEVICEMANAGERIZLUCHATELUI_H

#include <QWidget>

namespace Ui {
class DeviceManagerIzluchatelUI;
}

class DeviceManagerIzluchatelUI : public QWidget
{
    Q_OBJECT
    
public:
    explicit DeviceManagerIzluchatelUI(QWidget *parent = 0);
    ~DeviceManagerIzluchatelUI();
    
private:
    Ui::DeviceManagerIzluchatelUI *ui;
};

#endif // DEVICEMANAGERIZLUCHATELUI_H
