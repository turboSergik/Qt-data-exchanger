#include <QCoreApplication>

#include <QDebug>
#include <iostream>

std::optional<uint16_t> powerOfTwo(uint64_t a)
{
    if ((a & (a - 1)) != 0) return std::nullopt;
    if (a == 0) return std::nullopt;

    uint16_t b = a - 1;
    return uint16_t(__builtin_popcount(b));
}


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // input way doesnt matter, i think
    uint64_t a = 1024;

    auto power = powerOfTwo(a);

    if (power.has_value() == false) qDebug() << "The numer is not power of two \n";
    else qDebug() << "Power is" << power.value();


    // return app.exec();
}
