#include <QCoreApplication>
#include "simplemodule.h"


#include <CCLibXml.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleModule* pModule = new SimpleModule("SubscriberExample");

    pModule->start();

    sleep(50);

    pModule->stop();
    delete pModule;

    return 0;
}
