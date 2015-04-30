#include "mbaro.h"
#include <CCLibMath.h>

using namespace CC::MATH;
using namespace CC::ROS;
using namespace CC::MODULES;

mBARO::mBARO() :
    QROSModule("mBARO"),
    m_Device(),
    m_DeviceOk(false)
{    
    m_Publiher   = advertise<BAROPacket>("Navio/Barometer");

    m_Device.initialize();

    m_DeviceOk   = true;

    qDebug() << "mBARO::mBARO() Module Initialized(" << m_DeviceOk << ")";

    if (hasConf() == false) {
        setFrequency(m_rDefaultFreq);
    }
}

qbool mBARO::isReady() const
{
    return m_DeviceOk;
}

void mBARO::runningCode()
{
    if (m_DeviceOk == false) {
        qDebug() << "mBARO::runningCode() ERROR: Module is not properly initialized";
        this->stop();
    }

    m_Device.refreshPressure();
    usleep(10000); // Waiting for pressure data ready
    m_Device.readPressure();

    m_Device.refreshTemperature();
    usleep(10000); // Waiting for temperature data ready
    m_Device.readTemperature();

    m_Device.calculatePressureAndTemperature();

    m_Packet.temperature_degC        = m_Device.getTemperature();
    m_Packet.pressure_mbar           = m_Device.getPressure();
    m_Packet.header.stamp            = getTime();
    m_Packet.header.seq++;

    m_Publiher.publish(m_Packet);

}
