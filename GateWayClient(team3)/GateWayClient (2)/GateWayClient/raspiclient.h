#ifndef RASPICLIENT_H
#define RASPICLIENT_H

#include <QObject>
#include <QByteArrayList>
#include <QHash>
#include <QDebug>
#include "mnetwork.h"
#include "mserialport.h"


class RaspiClient : public QObject
{
    Q_OBJECT
public:
    RaspiClient(QObject *parent = 0);
    ~RaspiClient();

    void  start();
    void  initBoardMap();
    void  initDeviceMap();
    void  initDataMap();
    void  initFrameMap();
    void  initDataLenMap();

    void  initUpBoardMap();
    void  initUpDeviceMap();
    //void  initUpDataMap();
    void  initUpFrameMap();
    void  initUpDataLenMap();


signals:

public slots:
    void  netDataList(
            const QByteArrayList& list);
    void  serialDataList(const QByteArrayList& list);

private:
    MNetwork*    net;
    MSerialPort* serial;

    QHash<int,QByteArray>    boardMap;
    QHash<int,QByteArray>    deviceMap;
    QHash<int,QByteArray>    dataMap;
    QHash<int,QByteArray>    frameMap;
    QHash<int,QByteArray>    datalenMap;

    QHash<int,QByteArray>    upboardMap;
    QHash<int,QByteArray>    updeviceMap;
  //  QHash<int,QByteArray>    updataMap;
    QHash<int,QByteArray>    upframeMap;
    QHash<int,QByteArray>    updatalenMap;
};

#endif // RASPICLIENT_H







