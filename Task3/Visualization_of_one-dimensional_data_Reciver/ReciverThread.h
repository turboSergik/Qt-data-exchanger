#ifndef RECIVERTHREAD_H
#define RECIVERTHREAD_H

#include <string.h>
#include <iostream>

#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8080

#include <QThread>

class ReciverThread : public QThread
{
Q_OBJECT
public:

    ReciverThread(QString name);

    void run();

private:

    QString name;

};


#endif // RECIVERTHREAD_H
