#include <QCoreApplication>

#include <QDebug>


void swap_bits(uint16_t& a, uint8_t pos1, uint8_t pos2)
{
    /// I wrote this code at 5 am. Came out for a smoke.
    /// Came back 5 minutes later. Looked at the code and understood that I have no idea how it works.....

    if (pos1 > pos2) std::swap(pos1, pos2);

    uint16_t mask1 = a & (1 << pos1);
    uint16_t mask2 = a & (1 << pos2);

    a ^= (1 << pos1) | (1 << pos2);

    mask1 <<= pos2 - pos1;
    mask2 >>= pos2 - pos1;

    a |= mask1;
    a |= mask2;
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // input way doesnt matter, i think
    uint16_t a = 6; ///  110

    swap_bits(a, 0, 1);

    qDebug() << "a=" << a;

    // return app.exec();
}
