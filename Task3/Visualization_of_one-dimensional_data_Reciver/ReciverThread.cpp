#include "ReciverThread.h"

#include <QAbstractSocket>

ReciverThread::ReciverThread(QString name) : name(name)
{

}

void ReciverThread::run()
{
    int sock = 0, valread;
    struct sockaddr_in serv_addr;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        printf("\n Socket creation error \n");
        return;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0)
    {
        printf("\nInvalid address/ Address not supported \n");
        return;
    }

    while(1) {

        int connection_status = connect(sock, QOverload<QAbstractSocket::SocketError>::of(&QAbstractSocket::error),
                                        this, &QAbstractSocket::SocketError);

        if (connection_status >= 0)
        {
            std::cout << "New connection" << std::endl;
            int count = 0;

            while(1) {

                valread = read( sock , buffer, 1024);
                // std::cout << buffer << std::endl;

                count++;
                double yy = atof(buffer);
                std::cout << yy << " count=" << count << std::endl;

                memset(&buffer, 0, sizeof(buffer));

                if (valread == 0) {
                    // connection was closed

                    std::cout << "Connection closed" << std::endl;
                    sock = socket(AF_INET, SOCK_STREAM, 0);

                    break;
                }
            }
        }
    }

}
