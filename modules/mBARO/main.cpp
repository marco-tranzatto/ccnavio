#include <QCoreApplication>
#include <mbaro.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CC::MODULES::mBARO modBARO;

    modBARO.start();

    if (modBARO.isReady() == false) {
        qDebug() << "mBARO::main ERROR, unable to run the process";
    }

    return a.exec();
}
