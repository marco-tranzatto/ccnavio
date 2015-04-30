#include "simplemodule.h"
#include <QDebug>
#include <std_msgs/String.h>
#include <std_msgs/Int32.h>

SimpleModule::SimpleModule(QString sName) : QROSModule(sName) {
    message = advertise<std_msgs::String>("chatter");
    counter = advertise<std_msgs::Int32>("counter");
    custom  = advertise<IMUPacket>("custom_message");
    time0   = getTime();
}

void SimpleModule::runningCode() {
    static std_msgs::Int32 cnt;
    IMUPacket customPkt;
    std_msgs::String msgPkt;
    std::stringstream ss;
    TimeDuration diff = getTime() - time0;
    ss << "porca miseria @" << diff.toSec();
    std::string      msg    =ss.str();

    qDebug() << "Publisher: sending msg on topic <" << QString::fromStdString(message.getTopic()) << ">: " << QString::fromStdString(msg);

    msgPkt.data             = msg;
    cnt.data++;

    customPkt.linear_acceleration_g.x = 1.0;
    customPkt.linear_acceleration_g.y = 2.0;
    customPkt.linear_acceleration_g.z = 3.0;


    message.publish(msgPkt);
    counter.publish(cnt);
    custom.publish(customPkt);
}




