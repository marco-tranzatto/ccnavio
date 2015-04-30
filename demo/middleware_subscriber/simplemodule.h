#ifndef SIMPLEMODULE_H
#define SIMPLEMODULE_H

#include <CCLibROS.h>
#include <cc_msgs/IMURaw.h>

using namespace CC::ROS;

class SimpleModule: public QROSModule {
Q_OBJECT

protected:
    typedef     cc_msgs::IMURaw     IMUPacket;
    Subscriber  chatterMessage;
    Subscriber  imuMessage;
    Time        time0;
    void onChatterReceived(const std_msgs::String::ConstPtr& msg);
    void onIMUReceived(const cc_msgs::IMURaw::ConstPtr& msg);

public:
    SimpleModule(QString sName);
    void runningCode();
};






#endif // SIMPLEMODULE_H
