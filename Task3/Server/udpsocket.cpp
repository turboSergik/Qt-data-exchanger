#include "udpsocket.h"

#include <QtMath>
#include <QThread>

UdpSocket::UdpSocket()
{
    socket = new QUdpSocket();
    // socket->bind(QHostAddress::Any, 8080);
}

void UdpSocket::ChangeStopSignal()
{
    this->signalToStop = 1 - this->signalToStop;
}

void UdpSocket::SendData()
{


    if (this->signalToStop == true) return;


    for (int i = 1; i <= 500; i++)
    {
        QByteArray data;
        data.clear();

        x += 0.001;

        double y = sin(x);

        data.append(QString::number(100 * y));

        QThread::msleep(1);
        socket->writeDatagram(data, QHostAddress::LocalHost, LISTENING_PORT);
    }


    /*
    QByteArray data;
    data.clear();

    double y = rand() % 100;

    data.append(QString::number(y));

    socket->writeDatagram(data, QHostAddress::LocalHost, 8080);

    // QThread::msleep(1);

    qDebug() << "Send " << y;
    */

}

