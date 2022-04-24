#ifndef SERIALPROTOCOL_H
#define SERIALPROTOCOL_H

#include <QObject>
#include <QByteArrayList>

#include <QDebug>

class SerialProtocol : public QObject
{
public:
    explicit SerialProtocol(QObject *parent = 0);
    ~SerialProtocol();

    QByteArray  package(
            const QByteArrayList& list);
    QByteArrayList  unpackage(QByteArray &data);

    QByteArray toZigbee(
            const QByteArray& data);
    QByteArray fromZigbee(
            const QByteArray& data);



private:
    //
};

#endif // SERIALPROTOCOL_H





