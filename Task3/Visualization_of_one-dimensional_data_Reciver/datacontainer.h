#ifndef DATACONTAINER_H
#define DATACONTAINER_H

#include <QLinkedList>
#include <mutex>

#include "forward.hpp"

class DataContainer
{
public:

    ~DataContainer();

    static DataContainer* GetInstance();

    void Push(const milliseconds x, const float y);
    void Pop();

    QList<dataPair>* GetContaiterPointer();

    size_t GetSize() const;

    std::mutex mutex;

private:

    DataContainer();
    void PushDataToContainerWithLock(dataPair data);

    static DataContainer* _instance;

    QList<dataPair>* data;


    milliseconds _timeLastData = std::chrono::milliseconds(0);
    QQueue<dataPair>* queue;

    // DataContainer(const DataContainer&) = delete;
    // DataContainer& operator=(const DataContainer&) = delete;

    int now = 0;
    int mx = -1;
};

#endif // DATACONTAINER_H
