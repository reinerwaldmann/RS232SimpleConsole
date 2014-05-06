#ifndef DEVICEMANAGERIZLUCHATEL_H
#define DEVICEMANAGERIZLUCHATEL_H

#include <QObject>
#include <QFile>
#include <QXmlStreamWriter>
#include <QDomText>
#include <QDomElement>

#include <QTextCodec>

#include "devicemanagerizluchatelui.h"
#include "devicelanjerome.h"
#include "devicers232rubin201.h"



#define MSG_ERROR 1
#define MSG_NEUTRAL 0
#define MSG_GOOD 2
#define MSG_DEBUG 3


//class PrincipalWindow;
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
    explicit DeviceManagerIzluchatel(/*PrincipalWindow * iprincipal, */int currentStandId=0, QObject *parent = 0);
    ~DeviceManagerIzluchatel ();

    /**
     * @brief measure
     * launches measurement process ASYNC, data is returned by other function
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
     * @brief DeviceManagerIzluchatel::addDevice
     * @param idevice
     * @param where 0 - to the active devices 1 - to the devices
     * @param desiredid
     * @return
     */
    //EC11
    int addDevice (Device *idevice, bool where,  int desiredid=0);

    /**
     * @brief initList
     * Инициирует список устройств, местоположение (какой к какому порту подключен) которых уже известно
     * @param ifilename
     * @return @return 0 при успехе, >0 при ошибке
     */

    int initList (QString ifilename);

    /**
     * @brief initActiveDeviceList
     *  Инициирует список устройств, местоположение (какой к какому порту подключен) которых ещё неизвестно
     * @param ifilename
     * @return 0 при успехе, >0 при ошибке
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


    /**
     * @brief wrLine
     * Установить состояние на линии контроллера. В данной версии для одного контроллера
     * @param numline
     * номер линии
     * @param state
     * состояние (1 - высокий, 0 -  низкий)
     * @return
     */
    int wrLine(int numline, bool state=1);

    int searchRS232DevicesOnPorts  (int idInActiveDevList);

    /**
    * @brief devicesHash hashlist of the devices
    * char is the id of the device, unique in this manager
    */
    QHash <int, Device * > devicesHash;
    QHash <int, Device * > activeDevicesHash; //ненайденное оборудование


    /**
     * @brief currentstandid идентификатор текущего стенда, который будет сличаться
     *с данными в файле предпочтений пользователя по устройствам.
     */
    int currentstandid;

    //PrincipalWindow * principal;
    DeviceManagerIzluchatelUI * UI;



protected:
    Controller * controller;  //покамест один, потом будет больше
    /* Подразумевая, что контроллер у нас один, можем сделать так:
при запросе к контроллеру прогоняем  список подключенных устройств.
Первый же найденный контроллер среди них мы объявляем текущим контроллером
Пока к реализации не применять.
*/





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
