#include "device.h"

Device::Device()
{
    isConnected=0;
    id=0; //если в ходе выполнения выплывает это значение,
    //это значит, что айди не присвоен почему-то
    reqtimer = new QTimer (this);
    connect (reqtimer, SIGNAL ( timeout()  ), this, SLOT (onPingFailed()) );
    reqtimer->setSingleShot(1);
    type=0; //не определен
    timeout  =5000;
    portIsSearched=0;
}


Device::~Device()
{

}


void Device::setID(int iid)
{
    id = iid;
}

int Device::getID()
{
    return id;
}


int  Device::getUniqueType()
{
    return uniqueType;
}

bool Device::getIsConnected()
{
    return isConnected;
}

QString Device::getName()
{
    return name;
}

QString Device::getDescription()
{
    return descr;
}


QString Device::getVariableComment()
{
    return variableComment;

}


void Device::setVariableComment(QString iVariableComment)
{
    variableComment=iVariableComment;
}

void Device::onPingFailed()
{


    setConnectedState(0);

}

int Device::getType()
{
    return type;

}


int Device::getTimeout()
{
    return timeout;
}


void Device::ms(QString imsg, int type)
{
    emit fireMsg(id,imsg,type);

}

Device * Device::returnMe()
{
    return this;
}

void Device::setConnectedState (bool isState)
{
if (isState==isConnected)
return;
    isConnected=isState;

if (isConnected)
{ emit fireConnected(id);}

else
{
if (!portIsSearched)  emit fireDisconnected(id);
}

}



QDomElement Device::getXMLPOsition ( QDomDocument * idoc)
{





    QDomElement node=idoc->createElement("device");
    ///node.setTagName("device");

    node.setAttribute("name", name);
    node.setAttribute("descr", descr);
    node.setAttribute("varComment", variableComment);
    node.setAttribute("id", id );
    node.setAttribute("unique_type", uniqueType);
    node.setAttribute("type", type);


    return node;



}


void Device::slotConnectx ()
{
    connectx();

}
