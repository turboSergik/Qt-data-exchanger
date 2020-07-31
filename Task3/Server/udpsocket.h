#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>

#include "settings.hpp"

class UdpSocket : public QObject
{

Q_OBJECT

public:
    UdpSocket();

    void SendData();
    void ChangeStopSignal();

signals:

 private:
    QUdpSocket* socket;

    bool signalToStop = true;
    float x = 0;
};

#endif // UDPSOCKET_H
