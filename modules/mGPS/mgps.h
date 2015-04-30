#ifndef MGPS_H
#define MGPS_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       mgps.h
 * \brief       GPS Module
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \ingroup     CCNAVIODEMO
 */

#include <CCLibROS.h>
#include <cc_msgs/GPSRaw.h>

#include <Navio/Ublox.h>

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup CCNAVIODEMO
 *  @{
 */

using namespace CC::ROS;

namespace CC {
namespace MODULES {

class mGPS : public QROSModule
{
private:
    typedef cc_msgs::GPSRaw     GPSPacket;
    static  const qreal         m_rDefaultFreq = 5.0;
protected:
    Ublox       m_Device;
    qbool       m_DeviceOk;
    GPSPacket   m_Packet;
    Publisher   m_Publiher;

public:
    mGPS();
    mGPS(QString sGPSID);

    qbool isReady() const;

protected:
    void runningCode();
};
}
}

/** @}*/

#endif // MGPS_H
