#ifndef NETPROTOCOL_H
#define NETPROTOCOL_H

#include <QObject>
#include <QByteArrayList>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

class NetProtocol : public QObject
{
    Q_OBJECT
public:
    explicit NetProtocol(QObject *parent = 0);
    ~NetProtocol();

    QByteArrayList  unpackage(
            const QJsonObject& obj);
    QJsonObject  package(
            const QByteArrayList& list);

signals:

public slots:
};

#endif // NETPROTOCOL_H
