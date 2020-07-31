#include "udpsocket.h"

UdpSocket::UdpSocket()
{

    qDebug() << "Create udp socket";

    socket = new QUdpSocket();
    socket->bind(QHostAddress::Any, 8080);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

int UdpSocket::kek = 0;


void UdpSocket::readyRead()
{
    qDebug() << "In ready read";

    QByteArray buffer;
    buffer.resize(socket->pendingDatagramSize());

    QHostAddress sender;
    quint16 sender_port;

    socket->readDatagram(buffer.data(), buffer.size(), &sender, &sender_port);

    qDebug() << "Message from: " << buffer;


    UdpSocket::kek++;


    qDebug() << QThread::currentThreadId();
}

