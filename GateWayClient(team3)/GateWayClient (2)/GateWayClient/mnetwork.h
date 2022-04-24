#ifndef MNETWORK_H
#define MNETWORK_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArrayList>
#include <QDebug>

#include "netprotocol.h"

class MNetwork : public QObject
{
    Q_OBJECT
public:
    explicit MNetwork(QObject *parent = 0);
    ~MNetwork();

    //settings and connect to host
    bool init(QString ip = "localhost", int port = 10000);
    //disconnect from host
    void close();
    //judge status of network
    bool isConnected();
    //analysis data
    void analysisDataFrame(const QByteArray& frame);//const QByteArray& frame
    //write data to network
    qint64  writeData(const QByteArray& data);
    void  analysisJson(const QByteArrayList& list);

signals:
    void  netDataReceived(
            const QByteArrayList&);
    void  netDataSend(const QJsonObject&);

public slots:
    void  onClientDataReceived();
    void  onDisconnectedHandle();
    void  onClientDataSend(const QJsonObject&);



private:
    bool           _isConnected;
    QByteArray     dataBuffer;
    QTcpSocket*    socket;

    NetProtocol*   protocol;
};

#endif // MNETWORK_H







