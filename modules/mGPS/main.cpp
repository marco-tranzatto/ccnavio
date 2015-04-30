#include <QCoreApplication>
#include <mgps.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CC::MODULES::mGPS modGPS;

    modGPS.start();

    if (modGPS.isReady() == false) {
        qDebug() << "mGPS::main ERROR, unable to run the process";
    }

    return a.exec();
}
