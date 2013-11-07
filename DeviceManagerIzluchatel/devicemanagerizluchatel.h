#ifndef DEVICEMANAGERIZLUCHATEL_H
#define DEVICEMANAGERIZLUCHATEL_H

#include <QObject>
#include "./principalwindow.h"
#include "device.h"
#include "devicemanagerizluchatelui.h"


class PrincipalWindow;
class Device;

/**
 * @brief The DeviceManagerIzluchatel class
 *Must be a generic class, but smf prevented me to. It's a manager for all of the devices
 */
class DeviceManagerIzluchatel : public QObject
{
    Q_OBJECT
public:
    explicit DeviceManagerIzluchatel(PrincipalWindow * iprincipal,  QObject *parent = 0);


    /**
     * @brief measure
     * launches measurement process ASYNC, data is returned by other function
     * @param slt
     * @param out
     * @return 0 if OK, 1 if device is known to be offline
     */
    char measure (char slt, char out);

    /**
     * @brief checkAllOK
     * checks all devices
     * @return if all the devices are OK
     */

    bool checkAllOK ();


    /**
     * @brief connectALL
     *connects everything
     */
    void connectALL ();


    /**
     * @brief connectx connects the device
     * @param id of the device in the devices hash
     */
    void connectx (char id);

    void disconnectAll ();

    void disconnectx (char id);


    /**
     * @brief acceptMessagelauched by slot of the device (like readyRead slot)
     *basically relays the message to principal. Detects, what type of a message it is
     *and relays it to the proper function.
     * @param msg message itself
     * @param id id of the device in the list
     * @param type type of the message (0 - normal, 1 - error), or some other types
     */
    void acceptMessage (QString msg, int id, int type);



    /**
     * @brief addDevice
     * we add the device to the list, assign it an id that it'll have in the hash
     * @param idevice devices
     * @return 0 all is OK 1 same id already present
     */
    char addDevice (Device * idevice);





    /**
     * @brief devicesHash hashlist of the devices
     */
    QHash <char, Device * > devicesHash;

    PrincipalWindow * principal;
    DeviceManagerIzluchatelUI * UI;




signals:
    
public slots:
    
};

#endif // DEVICEMANAGERIZLUCHATEL_H
