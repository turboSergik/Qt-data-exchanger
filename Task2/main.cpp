#include <QCoreApplication>

#include <QDebug>
#include <QVector>


void FillDataFromString(std::string s, QVector<uint32_t>& source)
{
    uint32_t val = 0;

    for (size_t i = 0; i < s.size(); i++)
    {

        if (s[i] == '.' && source.size() < 4)
        {
            source.push_back(val);
            val = 0;
        }
        else if (s[i] >= '0' && s[i] <= '9')
        {
            val = val * 10 + s[i] - '0';
        }
        else if (s[i] == '/')
        {
            break;
        }
        else throw std::exception();
    }
    source.push_back(val);

    if (source.size() != 4) throw std::exception();
}


std::string GetBroadcastAddress(std::string address, std::string mask)
{
    QVector<uint32_t> addresses;
    QVector<uint32_t> masks;

    addresses.clear();
    masks.clear();

    FillDataFromString(address, addresses);
    FillDataFromString(mask, masks);

    QVector<uint32_t> res;

    for (int i = 0; i < 4; i++)
    {
        res.push_back(addresses[i] | ((masks[i] ^ ((1 << 8) - 1))));
    }

    std::string result = "";
    for (int i = 0; i < 4; i++)
    {
        result = result + std::to_string(res[i]);
        if (i != 3) result = result + ".";
    }

    return result;
}



int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // input way doesnt matter, i think

    std::string address = "192.168.5.138/24";
    std::string mask = "255.255.255.0";

    try
    {
        std::string result = GetBroadcastAddress(address, mask);
        qDebug() << QString::fromStdString(result);
    }
    catch(...)
    {
        qDebug() << "Wrong data!";
    }

    // 192.168.5.255 correct for this sample

    // return app.exec();
}
