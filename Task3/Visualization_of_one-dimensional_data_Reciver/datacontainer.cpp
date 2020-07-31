#include "datacontainer.h"

#include "QDebug"

DataContainer* DataContainer::_instance = nullptr;

DataContainer::DataContainer()
{
    data = new QList<QPair<milliseconds, float> >();
    queue = new QQueue<dataPair>();
}

DataContainer::~DataContainer()
{
    delete data;
    delete queue;
    delete _instance;
}

DataContainer *DataContainer::GetInstance()
{
    if (_instance == nullptr)
        _instance = new DataContainer();

    return  _instance;
}

void DataContainer::Push(const milliseconds x, const float y)
{
    // if (queue->size() != 0 && queue->front().first == x) return;

    queue->push_back({x, y});

    if (queue->size() > 0)
    {
        mutex.lock();

        while(queue->size())
        {
            PushDataToContainerWithLock(queue->front());
            queue->pop_front();
        }

        mutex.unlock();
    }
}

void DataContainer::PushDataToContainerWithLock(dataPair dataToPush)
{

    data->push_back({dataToPush.first, dataToPush.second});

    // save memory and speeds up rendering
    if (data->size() > 5000000) data->pop_front();
}

void DataContainer::Pop()
{
    data->pop_front();
}

QList<dataPair>* DataContainer::GetContaiterPointer()
{
    return data;
}

size_t DataContainer::GetSize() const
{
    return data->size();
}


