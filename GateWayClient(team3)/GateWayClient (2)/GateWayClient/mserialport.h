#ifndef MSERIALPORT_H
#define MSERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArrayList>

#include "dataqueue.h"
#include "serialprotocol.h"

class MSerialPort : public QObject
{
    Q_OBJECT
public:
    explicit MSerialPort(QObject *parent = 0);
    ~MSerialPort();

    QByteArray judgeComplete();

    void init();/*const QString& name,
              QSerialPort::BaudRate br = QSerialPort::Baud57600,
              QSerialPort::DataBits db = QSerialPort::Data8,
              QSerialPort::StopBits sb = QSerialPort::OneStop,
              QSerialPort::Parity pr = QSerialPort::NoParity,
              QSerialPort::FlowControl fc = QSerialPort::NoFlowControl);*/
    void close();
    void sendData(
        const QByteArrayList& list);
    bool isConnected();

    void analysisDataFrame();

signals:
    void  writeFinished();
    void  dataReceived(const QByteArrayList&);

public slots:
    void  onDataQueueHandle();
    void  onSerialDataReceived();

private:
    SerialProtocol*    protocol;
    QSerialPort   *    serial;
    bool               _isConnected;
    bool               _isWritable;
    QByteArray         dataBuffer;
    QByteArray         dataBuffer2;
    DataQueue     *    dataQueue;
};

#endif // MSERIALPORT_H







