#ifndef DEVICELAN_H
#define DEVICELAN_H

#include "device.h"
#include <QTcpSocket>
#include <QTimer>

class DeviceLAN : public Device
{
public:
    DeviceLAN();
};

#endif // DEVICELAN_H
