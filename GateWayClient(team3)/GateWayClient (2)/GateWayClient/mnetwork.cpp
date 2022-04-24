#include "mnetwork.h"

MNetwork::MNetwork(QObject *parent) : QObject(parent)
{
    dataBuffer.clear();
    _isConnected = false;
    protocol = new NetProtocol(this);
    socket = new QTcpSocket(this);
    connect(socket,SIGNAL(readyRead()),this,SLOT(onClientDataReceived()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(onDisconnectedHandle()));
    connect(this,SIGNAL(netDataSend(QJsonObject)),this,SLOT(onClientDataSend(QJsonObject)));
}

MNetwork::~MNetwork()
{

}

bool MNetwork::init(QString ip, int port)
{
    if(socket && !_isConnected)
    {
        socket->connectToHost(ip,  port);
        if(socket->waitForConnected())
        {
            _isConnected = true;
            qDebug() <<"okkkk" ;
            return true;
        }
    }
    return false;
}

void MNetwork::close()
{
    if(!isConnected()) return;
    _isConnected = false;
    socket->disconnectFromHost();
}

bool MNetwork::isConnected()
{
    return _isConnected;
}

//void MNetwork::analysisDataFrame()
//{
//    //qDebug() <<"okkkk" ;
//    QJsonDocument doc = QJsonDocument::fromJson(dataBuffer);
//    dataBuffer.clear();
//    qDebug() <<"Obeject: " << doc.object();
//    QByteArrayList list=protocol->unpackage(doc.object());
//   // qDebug()<<"list:"<<list;
//    if(list.isEmpty())return;
//    emit netDataReceived(list);
//}

void MNetwork::analysisDataFrame(const QByteArray &frame)
{
    qDebug() <<"fenxi" ;
    QJsonDocument doc = QJsonDocument::fromJson(frame);
    qDebug() << "Object:" << doc.object();
    QByteArrayList  list =
        protocol->unpackage(doc.object());
    if(list.isEmpty()) return;
    emit netDataReceived(list);
}

qint64 MNetwork::writeData(const QByteArray &data)
{
    if(!isConnected()) return 0;
    qint64 len = socket->write(data);
    socket->waitForBytesWritten(200);
    return len;
}

void MNetwork::analysisJson(const QByteArrayList &list)
{
    //qDebug()<<"nisyige:"<<list;
    QJsonObject qjson=protocol->package(list);
    //qDebug()<<"qjson:"<<qjson;
    emit netDataSend(qjson);
}
//void MNetwork::onClientDataReceived(){
//    if(socket->bytesAvailable())
//    {
//        dataBuffer.append(socket->readAll());
//    }

//    //judge complete frame or not
//    analysisDataFrame();
//}

void MNetwork::onClientDataReceived()
{
    if(socket->bytesAvailable()){
        dataBuffer.append(socket->readAll());
    }
    QByteArray  split("END");
    if(!dataBuffer.contains(split))
        return;
    int len = dataBuffer.indexOf(split);
    QByteArray frame =
            dataBuffer.mid(0, len);
    dataBuffer.remove(0, len+3);
    analysisDataFrame(frame);
}

void MNetwork::onDisconnectedHandle()
{
    //code here ...
    this->close();
}

void MNetwork::onClientDataSend(const QJsonObject & json)
{
    qDebug()<<"json:"<<json;
    this->socket->write(QJsonDocument(json).toJson()+"END");
    qDebug()<<"success!!!!!!!!!!!!!!!!!";
}






