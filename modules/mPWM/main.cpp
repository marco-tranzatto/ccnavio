#include <QCoreApplication>
#include <mpwm.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    CC::MODULES::mPWM modPWM;

    modPWM.start();

    if (modPWM.isReady() == false) {
        qDebug() << "mPWM::main ERROR, unable to run the process";
    }

    return a.exec();
}
