#ifndef DEVICEMANAGERIZLUCHATEL_H
#define DEVICEMANAGERIZLUCHATEL_H

#include <QObject>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDomText>
#include <QDomElement>



#include "device.h"
#include "./principalwindow.h"
#include "devicemanagerizluchatelui.h"


#define MSG_ERROR 1
#define MSG_NEUTRAL 0
#define MSG_GOOD 2
#define MSG_DEBUG 3


class PrincipalWindow;
class Device;
class DeviceManagerIzluchatelUI;

/**
 * @brief The DeviceManagerIzluchatel class
 *Must be a generic class, but smf prevented me to. It's a manager for all of the devices
 */
class DeviceManagerIzluchatel : public QObject
{
    Q_OBJECT
public:
    //EC1
    explicit DeviceManagerIzluchatel(PrincipalWindow * iprincipal, int currentStandId=0, QObject *parent = 0);
    ~DeviceManagerIzluchatel ();

    /**
     * @brief measure
     * launches measurement process ASYNC, data is returned by ot her function
     * @param id is the id of the device in deviceshash
     * @return 0 if OK, 1 if device is known to be offline
     */
    //EC2
    int measure (int id, QString type);

    /**
     * @brief checkAllOK
     * checks all devices
     * @return 0 if all the devices are connected, 1 if some of then no, 2 if number
     * of devices is not as specified
     *  @param number if set, then we also check, that a sertain number of devices is
     *  connected.
     */

    //EC3
    /**
     * @brief checkAllOK
     * @return 0 if all devices in the hash are connected
     *1 if some of them are not connected
     */
    int checkAllOK ();

    /**
     * @brief connectALL
     *connects everything
     */
    //EC4
    int connectALL ();


    //EC6
    int disconnectAll ();


    /**
     * @brief acceptMessagelauched by slot of the device (like readyRead slot)
     *basically relays the message to principal. Detects, what type of a message it is
     *and relays it to the proper function.
     * @param msg message itself
     * @param id id of the device in the list
     * @param type type of the message (0 - normal, 1 - error), or some other types
     */
    //EC8


    /**
     * @brief addDevice
     * we add the device to the list, assign it an id that it'll have in the hash
     * @param idevice devices
     * @return 0 all is OK 1 same id already present
     */
    //EC11
    int addDevice (Device *idevice, bool where,  int desiredid=0);


    /*inits the deviceshashs*/
    int initList (QString ifilename);
     /**
     * @brief devicesHash hashlist of the devices
     * char is the id of the device, unique in this manager
     */

    int initActiveDeviceList (QString ifilename);

    /**
     * @brief savePositionsOftheDevices
     * saves ports and optionally other settings of currently connected devices to the
     * xml file. Every device produces a verion of xml by itself.
     * @param ifilename
     * @return
     */

    int savePositionsOftheDevices (QString ifilename);



    void   setStandID(int id);
    int getStandID();


    QHash <int, Device * > devicesHash;
    QHash <int, Device * > activeDevicesHash; //ненайденное оборудование


    /**
     * @brief currentstandid идентификатор текущего стенда, который будет сличаться
     *с данными в файле предпочтений пользователя по устройствам.
     */
    int currentstandid;

    PrincipalWindow * principal;
    DeviceManagerIzluchatelUI * UI;



    int searchRS232DevicesOnPorts  (int idInActiveDevList);


signals:

    void fireTransitMeasData(int id,  double value, QString type);
    void fireDeviceDisconnected(int id);
    
public slots:
    void slotAcceptMessage (int id, QString msg, int type);
    void slotAcceptMeausure (int id, double value, QString type);
    void slotAcceptDeviceConnected (int id );
    void slotAcceptDeviceDisconnected (int id);


};

#endif // DEVICEMANAGERIZLUCHATEL_H
