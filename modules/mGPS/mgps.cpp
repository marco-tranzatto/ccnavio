#include "mgps.h"
#include <CCLibMath.h>

using namespace CC::MATH;
using namespace CC::ROS;
using namespace CC::MODULES;

mGPS::mGPS() : QROSModule("mGPS"), m_DeviceOk(false)
{    
    m_Publiher   = advertise<GPSPacket>("Navio/Gps");
    m_DeviceOk   = m_Device.testConnection();
    qDebug() << "mGPS::mGPS() Module Initialized(" << m_DeviceOk << ")";

    if (hasConf() == false) {
        setFrequency(m_rDefaultFreq);
    }
}

qbool mGPS::isReady() const
{
    return m_DeviceOk;
}

void mGPS::runningCode()
{
    if (m_DeviceOk == false) {
        qDebug() << "mGPS::runningCode() ERROR: Module is not properly initialized";
        this->stop();
    }

    std::vector<double> pos_data;

    if (m_Device.decodeSingleMessage(Ublox::NAV_POSLLH, pos_data) == 1)
    {
        m_Packet.latitude_deg    = pos_data[2]/10000000.0;
        m_Packet.longitude_deg   = pos_data[1]/10000000.0;
        m_Packet.altitude_m      = pos_data[3]/1000.0;
        m_Packet.gps_time_s.fromSec(pos_data[0]/1000.0);

        m_Packet.header.stamp    = getTime();
        m_Packet.header.seq++;
    }

    if (m_Device.decodeSingleMessage(Ublox::NAV_STATUS, pos_data) == 1)
    {
        qbool bGpsFix  = (((int)pos_data[1] & 0x01) > 0);
        qbool bPublish = false;

        switch((int)pos_data[0]){
            case 0x00:  /* no fix */
            case 0x01:  /* dead reckoning only */
            case 0x05:  /* Time only fix */;
            default:    /* Reserved value. Current state unknown */
                        break;

            case 0x02:  /* 2D-fix */
            case 0x03:  /* 3D-fix */
            case 0x04:  /* GPS + dead reckoning combined */
                        bPublish = true;
                        break;


        }

        if ((bGpsFix == true) && (bPublish == true)) {
            m_Publiher.publish(m_Packet);
        }
    }
}
