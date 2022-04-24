#include "serialprotocol.h"

SerialProtocol::SerialProtocol(QObject *parent) : QObject(parent)
{

}

SerialProtocol::~SerialProtocol()
{

}

QByteArray SerialProtocol::package(const QByteArrayList &list)
{
    //qDebug() << "serial protocol:" << list;
    if(list.isEmpty()) return QByteArray("");
    QByteArray  frame;
    //mei yong list
    //Example: 01 03 00 10 00 01
    int board,frametype,deviceid,datalen,data;
    sscanf(list.at(0),"%d",&board);
    sscanf(list.at(1),"%d",&frametype);
    sscanf(list.at(2),"%d",&deviceid);
    sscanf(list.at(3),"%d",&datalen);
    sscanf(list.at(4),"%d",&data);

     //datalen=list.size();
        qDebug()<<"bid:"<<board;
        qDebug()<<"fid:"<<frametype;
        qDebug()<<"deid:"<<deviceid;
        qDebug()<<"dalid:"<<datalen;
        qDebug()<<"daid:"<<data;
    switch (board) {
            case 1:
                frame[0]=0x07;
                break;
            case 2:
                frame[0]=0x07;
                break;
            case 3:
                frame[0]=0x08;
                break;
            case 4:
                frame[0]=0x01;
                break;
            case 5:
                frame[0]=0x01;
                break;
            case 6:
                frame[0]=0x06;
                break;
            default:
                break;

            }

            switch (frametype) {
            case 1:
                frame[1]=0x02;
                break;
            case 2:
                frame[1]=0x02;
                break;
            case 3:
                frame[1]=0x02;
                break;
            case 4:
                frame[1]=0x02;
                break;
            case 5:
                frame[1]=0x02;
                break;
            case 6:
                frame[1]=0x02;
                break;
            default:
                break;

            }

            switch (deviceid) {
            case 1:
                frame[2]=0x01;
                break;
            case 2:
                frame[2]=0x03;
                break;
            case 3:
                frame[2]=0x01;
                break;
            case 4:
                frame[2]=0x03;
                break;
            case 5:
                frame[2]=0x01;
                break;

            case 6:
                frame[2]=0x01;
                break;
            default:
                break;
            }

            switch (datalen) {
            case 1:
                frame[3]=0x01;
                break;
            case 2:
                frame[3]=0x01;
                break;
            case 3:
                frame[3]=0x01;
                break;
            case 4:
                frame[3]=0x01;
                break;
            case 5:
                frame[3]=0x02;
                break;

            case 6:
                frame[3]=0x01;
                break;
            default:
                break;


            }


            switch (data) {
            case 11:
                frame[4]=0x01;
                break;
            case 10:
                frame[4]=0x00;
                break;
            case 21:
                frame[4]=0x01;
                break;
            case 20:
                frame[4]=0x00;
                break;
            case 31:
                frame[4]=0x01;
                break;

            case 40:
                frame[4]=0x00;
                break;

            case 41:
                frame[4]=0x01;
                break;

            case 42:
                frame[4]=0x02;
                break;
            case 43:
                frame[4]=0x04;
                break;

            case 50:
                frame[4]=0x01;
                frame[5]=0x00;
                break;
            case 51:
                frame[4]=0x01;
                frame[5]=0x01;
                break;
            case 52:
                frame[4]=0x01;
                frame[5]=0x0A;
                break;
            case 53:
                frame[4]=0x01;
                frame[5]=0x14;
                break;
            case 60:
                frame[4]=0x00;
                break;
            case 61:
                frame[4]=0x1E;
                break;
            case 62:
                frame[4]=0x3C;
                break;
            case 63:
                frame[4]=0x5A;
                break;
            default:
                break;

            }
   // qDebug()<<"frame:"<<frame;
    return frame;
}

QByteArrayList SerialProtocol::unpackage( QByteArray &data)
{
    //qDebug()<<"uyfgsadfhhhhhhhhh:"<<data[0];



//    QByteA


    //UP UP UP
        QByteArrayList list;
        //board 2
        if (data[0]==2) {

                //device
                if(data[2]==1){//CO2

                    list.append(QByteArray("3"));
                    list.append(QByteArray("3"));
                    list.append(QByteArray("3"));
                    list.append(QByteArray("3"));

                    data.remove(0,4);
                    list.append(data);


                    }
                //device
                else if (data[2]==3) {//guangzhao

                    list.append(QByteArray("2"));
                    list.append(QByteArray("2"));
                    list.append(QByteArray("2"));
                    list.append(QByteArray("2"));

                    data.remove(0,4);
                    list.append(data);

                }
                else if (data[2]==4) {//ziwaixian

                    list.append(QByteArray("5"));
                    list.append(QByteArray("5"));
                    list.append(QByteArray("5"));
                    list.append(QByteArray("5"));

                    data.remove(0,4);
                    list.append(data);


                }


            }



       //board 3
       else if (data[0]==3) {

            if(data[2]==1){//fog

                list.append(QByteArray("6"));
                list.append(QByteArray("6"));
                list.append(QByteArray("6"));
                list.append(QByteArray("6"));

                data.remove(0,4);
                list.append(data);



            }
            else if (data[2]==2) {//CH4
                list.append(QByteArray("9"));
                list.append(QByteArray("9"));
                list.append(QByteArray("9"));
                list.append(QByteArray("9"));

                data.remove(0,4);
                list.append(data);





            }
            else if (data[2]==3) {//hongwai

                list.append(QByteArray("8"));
                list.append(QByteArray("8"));
                list.append(QByteArray("8"));
                list.append(QByteArray("8"));
                data.remove(0,4);
                list.append(data);



            }
            else if (data[2]==4) {//fire light
                list.append(QByteArray("7"));
                list.append(QByteArray("7"));
                list.append(QByteArray("7"));
                list.append(QByteArray("7"));
                data.remove(0,4);
                list.append(data);


            }



       }

       else if (data[0]==4) {

            if(data[2]==1) {//PM2.5
                list.append(QByteArray("4"));
                list.append(QByteArray("4"));
                list.append(QByteArray("4"));
                list.append(QByteArray("4"));
                data.remove(0,4);
                list.append(data);

            }
            else if (data[2]==2) { //humidity and tempratrue
                list.append(QByteArray("1"));
                list.append(QByteArray("1"));
                list.append(QByteArray("1"));
                list.append(QByteArray("1"));
                data.remove(0,4);
                list.append(data);
            }


       }

       else if (data[0]==5) {
            if(data[2]==3){
                list.append(QByteArray("10"));
                list.append(QByteArray("10"));
                list.append(QByteArray("10"));
                list.append(QByteArray("10"));

                data.remove(0,4);
                list.append(data);

            }
            else if (data[2]==4) {
                list.append(QByteArray("11"));
                list.append(QByteArray("11"));
                list.append(QByteArray("11"));
                list.append(QByteArray("11"));
                data.remove(0,4);
                list.append(data);

            }



       }
    // qDebug()<<"success!!!!!!!!!!!!!!!!!:"<<list;

        return list;

    //
//    if(data[0]==1){
//       list.append("1");
//    }
//    if(data[1]==2){
//        list.append("2");
//    }
  //  qDebug()<<"difuhnkdj:"<<list;
//    return list;

}

QByteArray SerialProtocol::toZigbee(const QByteArray &data)
{
    if(data.isEmpty()) return QByteArray("");
    QByteArray frame =
            QByteArray::fromHex("BBAA00FFFF");
    int len = data.size() + 8;
   // QString key=QString::number(len,16);
  //  qDebug()<<"nicaizheshisha:"<<key;
    frame[2] = len;
    qDebug()<<"len:"<<len;
    frame.append(data);
    int check=data[0];
        for(int i=1;i<data.size();i++){
            check^=data[i];
        }
     int a=data.size()+5;
     frame[a]=check;
     frame[a+1]=0xEE;
     frame[a+2]=0xFF;

    return frame;
}

QByteArray SerialProtocol::fromZigbee(const QByteArray &data)
{
    QByteArray  frame = data;
    int len=data.size();


    QByteArray  end=QByteArray::fromHex("EEFF");
    if(data.right(2)==end)
    {
        frame.remove(len-2,len);
    }else{
        frame.clear();
        return QByteArray("");
    }
   // qDebug()<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiii:"<<frame;

    frame.remove(0, 5);
  //  qDebug()<<"iiiiiiiiiiiiiiiiiiiiiiiiiiiii:"<<frame;
    return frame;
}

