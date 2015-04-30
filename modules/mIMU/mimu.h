#ifndef MIMU_H
#define MIMU_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       mimu.h
 * \brief       IMU Module
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \ingroup     CCNAVIODEMO
 */

#include <CCLibROS.h>
#include <cc_msgs/IMURaw.h>

#include <Navio/MPU9250.h>

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup CCNAVIODEMO
 *  @{
 */

using namespace CC::ROS;

namespace CC {
namespace MODULES {

class mIMU : public QROSModule
{
private:
    typedef cc_msgs::IMURaw     IMUPacket;
    static  const qreal         m_rDefaultFreq = 25.0;
protected:
    MPU9250     m_Device;
    qbool       m_DeviceOk;
    IMUPacket   m_Packet;
    Publisher   m_Publiher;

public:
    mIMU();
    mIMU(QString sIMUID);

    qbool isReady() const;

protected:
    void runningCode();
};
}
}

/** @}*/

#endif // MIMU_H
