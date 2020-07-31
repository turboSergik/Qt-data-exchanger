#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include <QObject>
#include <QUdpSocket>

#include <QThread>

class UdpSocket : public QObject
{

Q_OBJECT

public:
    UdpSocket();

    static int kek;

signals:

public slots:
    void readyRead();

 private:
    QUdpSocket* socket;
};

#endif // UDPSOCKET_H
