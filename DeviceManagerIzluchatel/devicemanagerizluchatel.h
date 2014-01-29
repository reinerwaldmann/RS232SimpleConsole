#ifndef DEVICEMANAGERIZLUCHATEL_H
#define DEVICEMANAGERIZLUCHATEL_H

#include <QObject>
#include "./principalwindow.h"
#include "device.h"


#include "devicemanagerizluchatelui.h"

#include "devicefinder.h"


class PrincipalWindow;
class Device;
class DeviceManagerIzluchatelUI;
class DeviceFinder;

/**
 * @brief The DeviceManagerIzluchatel class
 *Must be a generic class, but smf prevented me to. It's a manager for all of the devices
 */
class DeviceManagerIzluchatel : public QObject
{
    Q_OBJECT
public:
    //EC1
    explicit DeviceManagerIzluchatel(PrincipalWindow * iprincipal,  QObject *parent = 0);

    /**
     * @brief measure
     * launches measurement process ASYNC, data is returned by ot her function
     * @param slt
     * @param out
     * @return 0 if OK, 1 if device is known to be offline
     */
    //EC2
    int measure (char slt, char out);

    /**
     * @brief checkAllOK
     * checks all devices
     * @return 0 if all the devices are connected, 1 if some of then no, 2 if number
     * of devices is not as specified
     *  @param number if set, then we also check, that a sertain number of devices is
     *  connected.
     */
    //EC3
    int checkAllOK (int number=0);


    /**
     * @brief connectALL
     *connects everything
     */
    //EC4
    int connectALL ();


    /**
     * @brief connectx connects the device
     * @param id of the device in the devices hash
     */
    //EC5
    int connectx (char id);

    //EC6
    int disconnectAll ();

    //EC7
    int disconnectx (char id);


    /**
     * @brief acceptMessagelauched by slot of the device (like readyRead slot)
     *basically relays the message to principal. Detects, what type of a message it is
     *and relays it to the proper function.
     * @param msg message itself
     * @param id id of the device in the list
     * @param type type of the message (0 - normal, 1 - error), or some other types
     */
    //EC8
    int acceptMessage (QString msg, int id, int type);

    //EC9
    int acceptMeausure (double value, int id, int type);

   //EC10
    int acceptPing (int id );






    /**
     * @brief addDevice
     * we add the device to the list, assign it an id that it'll have in the hash
     * @param idevice devices
     * @return 0 all is OK 1 same id already present
     */
    //EC11
    int addDevice (Device * idevice);


    //EC12
    void acceptPingFailed (int id);



    /**
     * @brief devicesHash hashlist of the devices
     * char is the id of the device, unique in this manager
     */
    QHash <char, Device * > devicesHash;

    PrincipalWindow * principal;
    DeviceManagerIzluchatelUI * UI;
    DeviceFinder * devfind;



signals:
    
public slots:
    
};

#endif // DEVICEMANAGERIZLUCHATEL_H
