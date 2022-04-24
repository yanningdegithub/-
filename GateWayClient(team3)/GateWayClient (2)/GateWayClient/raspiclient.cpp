#include "raspiclient.h"

RaspiClient::RaspiClient(QObject *parent) : QObject(parent)
{
    serial = new MSerialPort(this);

    net = new MNetwork(this);
    connect(net,
        SIGNAL(netDataReceived(QByteArrayList)),
        this,
        SLOT(netDataList(QByteArrayList)));
    connect(serial,
            SIGNAL(dataReceived(QByteArrayList)),
            this,
            SLOT(serialDataList(QByteArrayList)));

    initBoardMap();
    initDeviceMap();
    initFrameMap();
    initDataMap();
    initDataLenMap();

    initUpBoardMap();
    initUpFrameMap();
    initUpDeviceMap();
    initUpDataLenMap();
    //initUpDataMap();
}

RaspiClient::~RaspiClient()
{

}

void RaspiClient::start()
{
    if(!net) return;
    net->init("106.14.180.15", 10002);
    if(serial)
        serial->init();
}

void RaspiClient::initBoardMap()
{

    boardMap.insert(1, QByteArray("fengshan"));
    boardMap.insert(2, QByteArray("chuanglian"));
    boardMap.insert(3, QByteArray("mensuo"));
    boardMap.insert(4, QByteArray("deng1"));
    boardMap.insert(5, QByteArray("deng2"));
    boardMap.insert(6, QByteArray("chuang"));

}

void RaspiClient::initFrameMap()
{
    frameMap.insert(1, QByteArray("fengshan"));
    frameMap.insert(2, QByteArray("chuanglian"));
    frameMap.insert(3, QByteArray("mensuo"));
    frameMap.insert(4, QByteArray("deng1"));
    frameMap.insert(5, QByteArray("deng2"));
    frameMap.insert(6, QByteArray("chuang"));
}


void RaspiClient::initDeviceMap()
{
    deviceMap.insert(1, QByteArray("fengshan"));
    deviceMap.insert(2, QByteArray("chuanglian"));
    deviceMap.insert(3, QByteArray("mensuo"));
    deviceMap.insert(4, QByteArray("deng1"));
    deviceMap.insert(5, QByteArray("deng2"));
    deviceMap.insert(6, QByteArray("chuang"));
}
void RaspiClient::initDataLenMap()
{
    datalenMap.insert(1, QByteArray("fengshan"));
    datalenMap.insert(2, QByteArray("chuanglian"));
    datalenMap.insert(3, QByteArray("mensuo"));
    datalenMap.insert(4, QByteArray("deng1"));
    datalenMap.insert(5, QByteArray("deng2"));
    datalenMap.insert(6, QByteArray("chuang"));
}



void RaspiClient::initUpBoardMap()
{
    upboardMap.insert(1, QByteArray("wenshidu"));
    upboardMap.insert(2, QByteArray("guangzhao"));
    upboardMap.insert(3, QByteArray("CO2"));
    upboardMap.insert(4, QByteArray("PM2.5"));
    upboardMap.insert(5, QByteArray("ziwaixian"));
    upboardMap.insert(6, QByteArray("yanwu"));
    upboardMap.insert(7, QByteArray("huoguang"));
    upboardMap.insert(8, QByteArray("hongwai"));
    upboardMap.insert(9, QByteArray("CH4"));
    upboardMap.insert(10, QByteArray("duishe"));
    upboardMap.insert(11, QByteArray("fanshe"));
}


void RaspiClient::initUpFrameMap()
{
    upframeMap.insert(1, QByteArray("wenshidu"));
    upframeMap.insert(2, QByteArray("guangzhao"));
    upframeMap.insert(3, QByteArray("CO2"));
    upframeMap.insert(4, QByteArray("PM2.5"));
    upframeMap.insert(5, QByteArray("ziwaixian"));
    upframeMap.insert(6, QByteArray("yanwu"));
    upframeMap.insert(7, QByteArray("huoguang"));
    upframeMap.insert(8, QByteArray("hongwai"));
    upframeMap.insert(9, QByteArray("CH4"));
    upframeMap.insert(10, QByteArray("duishe"));
    upframeMap.insert(11, QByteArray("fanshe"));
}



void RaspiClient::initUpDeviceMap()
{
    updeviceMap.insert(1, QByteArray("wenshidu"));
    updeviceMap.insert(2, QByteArray("guangzhao"));
    updeviceMap.insert(3, QByteArray("CO2"));
    updeviceMap.insert(4, QByteArray("PM2.5"));
    updeviceMap.insert(5, QByteArray("ziwaixian"));
    updeviceMap.insert(6, QByteArray("yanwu"));
    updeviceMap.insert(7, QByteArray("huoguang"));
    updeviceMap.insert(8, QByteArray("hongwai"));
    updeviceMap.insert(9, QByteArray("CH4"));
    updeviceMap.insert(10, QByteArray("duishe"));
    updeviceMap.insert(11, QByteArray("fanshe"));
}


void RaspiClient::initUpDataLenMap()
{
    updatalenMap.insert(1, QByteArray("wenshidu"));
    updatalenMap.insert(2, QByteArray("guangzhao"));
    updatalenMap.insert(3, QByteArray("CO2"));
    updatalenMap.insert(4, QByteArray("PM2.5"));
    updatalenMap.insert(5, QByteArray("ziwaixian"));
    updatalenMap.insert(6, QByteArray("yanwu"));
    updatalenMap.insert(7, QByteArray("huoguang"));
    updatalenMap.insert(8, QByteArray("hongwai"));
    updatalenMap.insert(9, QByteArray("CH4"));
    updatalenMap.insert(10, QByteArray("duishe"));
    updatalenMap.insert(11, QByteArray("fanshe"));
}

//void RaspiClient::initUpDataMap()
//{
//    updataMap.insert(1, QByteArray("wenshidu"));
//    updataMap.insert(2, QByteArray("guangzhao"));
//    updataMap.insert(3, QByteArray("CO2"));
//    updataMap.insert(4, QByteArray("PM2.5"));
//    updataMap.insert(5, QByteArray("ziwaixian"));
//    updataMap.insert(6, QByteArray("yanwu"));
//    updataMap.insert(7, QByteArray("huoguang"));
//    updataMap.insert(8, QByteArray("hongwai"));
//    updataMap.insert(9, QByteArray("CH4"));
//    updataMap.insert(10, QByteArray("duishe"));
//    updataMap.insert(11, QByteArray("fanshe"));
//}



void RaspiClient::initDataMap()
{
    dataMap.insert(11, QByteArray("fs_open"));
    dataMap.insert(10, QByteArray("fs_close"));
    dataMap.insert(21, QByteArray("cl_open"));
    dataMap.insert(20, QByteArray("cl_close"));
    dataMap.insert(31, QByteArray("ms"));
    dataMap.insert(40, QByteArray("deng1_close"));
    dataMap.insert(41, QByteArray("deng1_R"));
    dataMap.insert(42, QByteArray("deng1_G"));
    dataMap.insert(43, QByteArray("deng1_Y"));
    dataMap.insert(50, QByteArray("deng2_close"));
    dataMap.insert(51, QByteArray("deng2_slight"));
    dataMap.insert(52, QByteArray("deng2_middle"));
    dataMap.insert(53, QByteArray("deng2_strong"));
    dataMap.insert(60, QByteArray("chuang_0"));
    dataMap.insert(61, QByteArray("chuang_30"));
    dataMap.insert(62, QByteArray("chuang_60"));
    dataMap.insert(63, QByteArray("chuang_90"));
}



void RaspiClient::netDataList(const QByteArrayList &list)
{
    QByteArrayList  tmp;
//    qDebug()<<"adfukjbdaufijkdgnijdk:"<<list;
    int  bid = boardMap.key(list.at(0));
    int fid=frameMap.key(list.at(1));
    int deid=deviceMap.key(list.at(2));
    int dalid=datalenMap.key(list.at(3));
    int daid=dataMap.key(list.at(4));
//    qDebug()<<"bid:"<<bid;
//    qDebug()<<"fid:"<<fid;
//    qDebug()<<"deid:"<<deid;
//    qDebug()<<"daid:"<<daid;
    QByteArray  boardid=QByteArray::number(bid);
    QByteArray  frameid= QByteArray::number(fid);
    QByteArray  deviceid = QByteArray::number(deid);
    QByteArray  datalenid = QByteArray::number(dalid);
    QByteArray  dataid = QByteArray::number(daid);
    tmp.append(boardid);
    tmp.append(frameid);
    tmp.append(deviceid);
    tmp.append(datalenid);
    tmp.append(dataid);

//    tmp.append(list.at(1));
   // qDebug()<<"tmpasfljadigfdoijdkgagijdsifjgjids:"<<tmp;
    //......
    serial->sendData(tmp);
}

void RaspiClient::serialDataList(const QByteArrayList &list)
{


    QByteArrayList  tmp;


    int boardkey=list.at(0).toInt();
    int framekey=list.at(1).toInt();
    int devicekey=list.at(2).toInt();
    int datalenkey=list.at(3).toInt();
    QByteArray  data=list.at(4);


    QByteArray board=upboardMap.value(boardkey);
    QByteArray frametype=upframeMap.value(framekey);
    QByteArray device=updeviceMap.value(devicekey);
    QByteArray datalen=updatalenMap.value(datalenkey);

    tmp.append(board);
    tmp.append(frametype);
    tmp.append(device);
    tmp.append(datalen);

    tmp.append(data);

    net->analysisJson(tmp);

}






