#ifndef RECEIVINGDATATHREAD_H
#define RECEIVINGDATATHREAD_H

#include <QThread>
#include <QObject>
#include <QUdpSocket>

#include "udpsocket.h"
#include "datacontainer.h"

#include "settings.hpp"

class ReceivingDataThread : public QThread
{
Q_OBJECT
public:

    ReceivingDataThread();
    ~ReceivingDataThread();

    void run() override;

    void setStopSignal(bool signal);

private:

    QUdpSocket* socket;

    bool signalToStop = false;
};

#endif // RECEIVINGDATATHREAD_H
