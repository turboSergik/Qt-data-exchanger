#include "receivingdatathread.h"

ReceivingDataThread::ReceivingDataThread()
{
}

ReceivingDataThread::~ReceivingDataThread()
{
    socket->disconnect();
    delete socket;
}

void ReceivingDataThread::run()
{
    int nOK = 0;
    int OK = 0;

    socket = new QUdpSocket();
    socket->bind(QHostAddress::Any, LISTENING_PORT);

    QByteArray buffer;

    QHostAddress sender;
    quint16 sender_port;

    bool ready = false;

    auto container = DataContainer::GetInstance();

    while(this->signalToStop == false) {

        // receive and check data

        while(!ready) {
            if (this->signalToStop == true) return;
            ready = socket->waitForReadyRead(1);
        }

        ready = false;

        buffer.resize(socket->pendingDatagramSize());
        socket->readDatagram(buffer.data(), buffer.size(), &sender, &sender_port);

        bool ok = false;
        float y = buffer.toFloat(&ok);
        milliseconds x = duration_cast< std::chrono::milliseconds>(
                    system_clock::now().time_since_epoch());

        if (ok == true) container->Push(x, y), OK++;
        else
        {
            nOK++;
            continue;
        }

    }
}

void ReceivingDataThread::setStopSignal(bool signal)
{
    this->signalToStop = signal;
}

