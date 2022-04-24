#include "mserialport.h"

MSerialPort::MSerialPort(QObject *parent) : QObject(parent)
{
//    QList<QSerialPortInfo> list=
//            QSerialPortInfo::availablePorts();
//    if(list.isEmpty()){
//        qDebug()<<"have not serial";
//        exit(0);
//    }
//    serial->setPortName(list[0].portName());
//    serial->setBaudRate(QSerialPort::Baud57600);
//    serial->setDataBits(QSerialPort::Data8);
//    serial->setStopBits(QSerialPort::OneStop);
//    serial->setParity(QSerialPort::NoParity);
//    serial->setFlowControl(QSerialPort::NoFlowControl);
//    if(!serial->open(QIODevice::ReadWrite))
//    {
//        qDebug() << "serial open error!";
//        _isConnected = false;
//        return;
//    }
//    qDebug() << "open serial successful!";
    _isConnected = false;
    _isWritable = false;
    dataBuffer.clear();
    dataBuffer2.clear();
    protocol = new SerialProtocol(this);
    dataQueue = new DataQueue(10, this);
    serial = new QSerialPort(this);
    connect(serial, SIGNAL(readyRead()),
            this,SLOT(onSerialDataReceived()));

    connect(this,SIGNAL(writeFinished()),
            this,SLOT(onDataQueueHandle()));
}

MSerialPort::~MSerialPort()
{

}

QByteArray MSerialPort::judgeComplete()
{
    QByteArray  head =
            QByteArray::fromHex("AABB");
   // qDebug()<<"ananlysisDataFrame2";
    if(dataBuffer.left(2) != head){
        if(dataBuffer.contains(head)){
            dataBuffer.remove(0,
                dataBuffer.indexOf(head));
        }else{
            dataBuffer.clear();
            return QByteArray("");
        }
    }
    if(dataBuffer.size() < 5)
        return QByteArray("");
//    qDebug()<<"ananlysisDataFrame4";
    QByteArray frame;
    int len = dataBuffer.at(2);
    if(len > dataBuffer.size())
        return QByteArray("");
   // qDebug()<<"ananlysisDataFrame5:"<<dataBu;
    frame = dataBuffer.mid(0, len);
    dataBuffer.remove(0, len);
   // qDebug()<<"dataBu123456789:"<<frame;
    return frame;
}

void MSerialPort::init()//const QString &name, QSerialPort::BaudRate br, QSerialPort::DataBits db, QSerialPort::StopBits sb, QSerialPort::Parity pr, QSerialPort::FlowControl fc)
{
    //if(name.isEmpty()) return;
    QList<QSerialPortInfo> list=
            QSerialPortInfo::availablePorts();
    if(list.isEmpty()){
        qDebug()<<"have not serial";
        exit(0);
    }
    serial->setPortName(list[0].portName());
    serial->setBaudRate(QSerialPort::Baud57600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setParity(QSerialPort::NoParity);
    serial->setFlowControl(QSerialPort::NoFlowControl);

//    serial->setPortName(name);
//    serial->setBaudRate(br);
//    serial->setDataBits(db);
//    serial->setStopBits(sb);
//    serial->setParity(pr);
//    serial->setFlowControl(fc);
    if(!serial->open(QIODevice::ReadWrite))
    {
        qDebug() << "serial open error!";
        _isConnected = false;
        return;
    }
    _isConnected = true;
    _isWritable = true;
    qDebug() << "open serial successful!";
}

void MSerialPort::close()
{
    if(isConnected())
        serial->close();
    _isConnected = false;
    _isWritable = false;
    dataBuffer.clear();
    while(dataQueue->size()){
        dataQueue->pop();
    }
}

void MSerialPort::sendData(const QByteArrayList &list)
{

    //init();
    //qDebug()<<"tmp:"<<list;
    //_isConnected=true;//yao shan
    if(!_isConnected) return;

   // qDebug()<<"qinaidenimanmanfei:"<<list;
    QByteArray frame =
            protocol->package(list);
    if(frame.isEmpty()) return;
    QByteArray data =
            protocol->toZigbee(frame);
    qDebug()<<"data:"<<data;
    if(data.isEmpty()) return;
    if(!dataQueue->push(data)){
        qDebug()<< "Queue is Full!";
    }
    // qDebug()<< "Queue:"<<dataQueue;
    emit  writeFinished();
}

bool MSerialPort::isConnected()
{
    return _isConnected;
}

void MSerialPort::analysisDataFrame()
{
    QByteArray  frame;
    QByteArray   data;
    QByteArrayList list;
   // while(1){
        frame = judgeComplete();
        if(frame.isEmpty()) return;

        data = protocol->fromZigbee(frame);


        if(data.isEmpty()) return;
        list = protocol->unpackage(data);
        emit dataReceived(list);
  //  }
}

void MSerialPort::onDataQueueHandle()
{
    if(!_isWritable) return;
    //qDebug()<<"nishiyigeshabi";
    if( isConnected() && dataQueue->size())
    {
         qDebug()<<"ni";
        QByteArray data = dataQueue->pop();

        if(data.isEmpty()) return;
        _isWritable = false;
//        QByteArray d=
//                QByteArray::fromHex("AABBCCDD");
         qDebug()<<"ninini:"<<data.toHex();
       // analysisDataFrame();//////////////////////ji de shan
        serial->write(data);
      //  serial->write(d);
        qDebug()<<"shi:";
        serial->waitForBytesWritten(200);
        _isWritable = true;
        emit  writeFinished();
    }
}

void MSerialPort::onSerialDataReceived()
{

        QByteArray  end =
                QByteArray::fromHex("EEFF");
        QByteArray   frame;
        if(serial->bytesAvailable()){
            frame.append(serial->readAll());
        }

        dataBuffer2.append(frame);
       // qDebug()<<"receive data22222:"<<dataBuffer2;
        if(frame.right(2)==end){
           // dataBuffer.append(frame);
            qDebug()<<"receive data:"<<dataBuffer2.toHex();
            dataBuffer=dataBuffer2;
            dataBuffer2.clear();
            analysisDataFrame();
            //dataBuffer.clear();
        }
}


