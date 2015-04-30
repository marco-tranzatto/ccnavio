#include "simplemodule.h"
#include <QDebug>

void SimpleModule::onChatterReceived(const std_msgs::String::ConstPtr& msg)
{
    qDebug() << "Subscriber received message on topic <" << QString::fromStdString(chatterMessage.getTopic()) << "> was received: " << QString::fromStdString(msg->data);
}


void SimpleModule::onIMUReceived(const cc_msgs::IMURaw::ConstPtr& msg)
{
    qDebug() << "Subscriber received message on topic <" << QString::fromStdString(imuMessage.getTopic()) << "> was received: ";
    qDebug() << msg->linear_acceleration_g.x << " "<< msg->linear_acceleration_g.y << " "<< msg->linear_acceleration_g.z;
}

SimpleModule::SimpleModule(QString sName) : QROSModule(sName) {

    chatterMessage  = subscribe("chatter",      this, &SimpleModule::onChatterReceived);
    imuMessage      = subscribe("custom_message",    this, &SimpleModule::onIMUReceived);
}

void SimpleModule::runningCode() {
    qDebug() << "Subscriber is Running";
}




