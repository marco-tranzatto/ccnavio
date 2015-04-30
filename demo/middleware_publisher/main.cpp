#include <QCoreApplication>
#include "simplemodule.h"


#include <CCLibXml.h>


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    SimpleModule* pModule = new SimpleModule("PublisherExample");

    pModule->start();

    sleep(25);

    pModule->stop();
    delete pModule;

    return 0;
}
