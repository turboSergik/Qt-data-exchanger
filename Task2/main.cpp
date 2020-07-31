#include <QCoreApplication>

#include <QDebug>
#include <QVector>


uint32_t GetBroadcastAddress(uint32_t address, uint32_t mask)
{
    uint8_t okstet1 = ((address >> 24) & ((1 << 8) - 1));
    uint8_t okstet2 = ((address >> 16) & ((1 << 8) - 1));
    uint8_t okstet3 = ((address >> 8)  & ((1 << 8) - 1));
    uint8_t okstet4 = ((address)       & ((1 << 8) - 1));

    uint8_t okstet1_2 = ((mask >> 24) & ((1 << 8) - 1));
    uint8_t okstet2_2 = ((mask >> 16) & ((1 << 8) - 1));
    uint8_t okstet3_2 = ((mask >> 8)  & ((1 << 8) - 1));
    uint8_t okstet4_2 = ((mask)       & ((1 << 8) - 1));

    okstet1_2 ^= ((1 << 8) - 1);
    okstet2_2 ^= ((1 << 8) - 1);
    okstet3_2 ^= ((1 << 8) - 1);
    okstet4_2 ^= ((1 << 8) - 1);

    uint32_t broadcast = ((okstet1 | okstet1_2) << 24) +
                         ((okstet2 | okstet2_2) << 16) +
                         ((okstet3 | okstet3_2) << 8) +
                         ((okstet4 | okstet4_2));

    return broadcast;
}



int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);


    uint32_t address = 3338731876;
    uint32_t mask = 4294967264;
    // broadcast for this -  3338731903

    uint32_t broadcast;

    try
    {
        broadcast = GetBroadcastAddress(address, mask);
        qDebug() << broadcast;
    }
    catch(...)
    {
        qDebug() << "Wrong data!";
    }



    // return app.exec();
}
