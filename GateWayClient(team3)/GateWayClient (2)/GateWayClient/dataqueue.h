#ifndef DATAQUEUE_H
#define DATAQUEUE_H

#include <QObject>
#include <QDebug>
#include <QList>

class DataQueue : public QObject
{
public:
    DataQueue(int size = 100, QObject *parent = 0);
    ~DataQueue();

    void  setMaxSize(int s);
    bool  isEmpty();
    bool  isFull();
    int   size();

    bool  push(const QByteArray& data);
    QByteArray pop();

private:
    int                    _maxSize;
    int                    _currSize;
    QList<QByteArray>      queue;
};

#endif // DATAQUEUE_H






