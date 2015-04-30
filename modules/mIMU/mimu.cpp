#include "mimu.h"
#include <CCLibMath.h>

using namespace CC::MATH;
using namespace CC::ROS;
using namespace CC::MODULES;

mIMU::mIMU() : QROSModule("mIMU"), m_DeviceOk(false)
{    
    m_Publiher   = advertise<IMUPacket>("Navio/Imu");

    m_Device.initialize();

    m_DeviceOk   = true;

    qDebug() << "mIMU::mIMU() Module Initialized(" << m_DeviceOk << ")";

    if (hasConf() == false) {
        setFrequency(m_rDefaultFreq);
    }
}

qbool mIMU::isReady() const
{
    return m_DeviceOk;
}

void mIMU::runningCode()
{
    if (m_DeviceOk == false) {
        qDebug() << "mIMU::runningCode() ERROR: Module is not properly initialized";
        this->stop();
    }

    m_Device.read_all();

    /*
     * Acceleration, angular velocities and magnetometer readings are provided in
     * the Body reference frame, which is a NED oriented frame
    */

    m_Packet.linear_acceleration_g.x = +m_Device.accelerometer_data[1];
    m_Packet.linear_acceleration_g.y = +m_Device.accelerometer_data[0];
    m_Packet.linear_acceleration_g.z = -m_Device.accelerometer_data[2];

    m_Packet.angular_speed_deg_s.x   = +m_Device.gyroscope_data[1];
    m_Packet.angular_speed_deg_s.y   = +m_Device.gyroscope_data[0];
    m_Packet.angular_speed_deg_s.z   = -m_Device.gyroscope_data[2];

    m_Packet.magnetic_field_uT.x     = m_Device.magnetometer_data[0];
    m_Packet.magnetic_field_uT.y     = m_Device.magnetometer_data[1];
    m_Packet.magnetic_field_uT.z     = m_Device.magnetometer_data[2];

    m_Packet.temperature_degC        = m_Device.temperature;

    m_Packet.header.stamp            = getTime();
    m_Packet.header.seq++;


    /*
    qDebug() << "mIMU::mIMU() " << m_Packet.linear_acceleration_g.x << ","
                                << m_Packet.linear_acceleration_g.y << ","
                                << m_Packet.linear_acceleration_g.z << "____"
                                << m_Packet.angular_speed_deg_s.x << ","
                                << m_Packet.angular_speed_deg_s.y << ","
                                << m_Packet.angular_speed_deg_s.z << "____"
                                << m_Packet.magnetic_field_uT.x << ","
                                << m_Packet.magnetic_field_uT.y << ","
                                << m_Packet.magnetic_field_uT.z;
    */

    m_Publiher.publish(m_Packet);

}
