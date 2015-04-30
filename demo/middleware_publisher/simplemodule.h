#ifndef SIMPLEMODULE_H
#define SIMPLEMODULE_H

#include <CCLibROS.h>
#include <cc_msgs/IMURaw.h>

using namespace CC::ROS;

class SimpleModule: public QROSModule {
Q_OBJECT

protected:
    typedef cc_msgs::IMURaw     IMUPacket;
    Publisher  message;
    Publisher  counter;
    Publisher  custom;
    Time       time0;
public:
    SimpleModule(QString sName);
    void runningCode();
};






#endif // SIMPLEMODULE_H
