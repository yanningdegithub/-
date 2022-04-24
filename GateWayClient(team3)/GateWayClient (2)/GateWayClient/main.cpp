#include <QCoreApplication>
#include "raspiclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    RaspiClient  rc;
    //MSerialPort  ms;
   // ms.init();
    rc.start();

    return a.exec();
}
