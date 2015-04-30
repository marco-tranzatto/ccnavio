#include <QCoreApplication>
#include <mimu.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CC::MODULES::mIMU modIMU;

    modIMU.start();

    if (modIMU.isReady() == false) {
        qDebug() << "mIMU::main ERROR, unable to run the process";
    }

    return a.exec();
}
