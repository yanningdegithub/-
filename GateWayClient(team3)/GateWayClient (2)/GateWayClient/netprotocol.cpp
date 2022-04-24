#include "netprotocol.h"

NetProtocol::NetProtocol(QObject *parent) : QObject(parent)
{

}

NetProtocol::~NetProtocol()
{

}

QByteArrayList NetProtocol::unpackage(
        const QJsonObject &obj)
{
    QByteArrayList  list;
    QByteArray board =obj.value("board").toString().toLatin1();
    QByteArray frame=obj.value("frametype").toString().toLatin1();
    list.append(board);
    list.append(frame);
    QByteArray device=obj.value("device").toString().toLatin1();
    list.append(device);
    QByteArray datalen=obj.value("datalen").toString().toLatin1();
    list.append(datalen);
    QByteArray data=obj.value("data").toString().toLatin1();
    list.append(data);

    //qDebug()<<"nishiwodexiaoyaxiaopingguo:"<<list;
    //.......
    return list;




}

QJsonObject NetProtocol::package(const QByteArrayList &list)
{
    //
   // qDebug()<<"listsend:"<<list;
    QJsonObject json;

    QByteArray board=list.at(0);
    QByteArray frametype=list.at(1);
    QByteArray device=list.at(2);
    QByteArray datalen=list.at(3);
    QByteArray data=list.at(4);

    quint8 str=data.mid(0,1).toHex().toUShort(Q_NULLPTR,16);
    quint8 str2=data.mid(1,1).toHex().toUShort(Q_NULLPTR,16);

    int    a=str*256+str2;
    QString    strBoard=QString(board);
    QString    strFrametype=QString(frametype);
    QString    strDevice=QString(device);
    QString    strDatalen=QString(datalen);
  //  QString    strData=QString(data);
    json.insert("board",strBoard);
    json.insert("frametype",strFrametype);
    json.insert("device",strDevice);
    json.insert("datalen",strDatalen);
    json.insert("data",a);

    if(board=="wenshidu"){
        json.insert("data1",str);
        json.insert("data2",str2);
    }

//    json.insert("PSc",c);
//    json.insert("directio",d);
    //qDebug()<<"json:"<<json;
    return json;
}

