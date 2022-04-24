#include "dataqueue.h"

DataQueue::DataQueue(int size, QObject *parent) : QObject(parent)
{
    _maxSize = size;
    _currSize = 0;
    queue.clear();
}

DataQueue::~DataQueue()
{
}

void DataQueue::setMaxSize(int s)
{
    this->_maxSize = s;
}

bool DataQueue::isEmpty()
{
    if(_currSize == 0) return true;
    return false;
}

bool DataQueue::isFull()
{
    if(_currSize == _maxSize) return true;
    return false;
}

int DataQueue::size()
{
    return _currSize;
}

bool DataQueue::push(const QByteArray &data)
{
    if(isFull()||data.isEmpty()) return false;
//    queue.append(data);
    qDebug()<<"dsghs";
    queue.push_back(data);
    _currSize ++;
    return true;
}

QByteArray DataQueue::pop()
{
    if(isEmpty()) return QByteArray("");
    QByteArray frame = queue.at(0);
    queue.pop_front();
    _currSize --;
    return frame;
}





