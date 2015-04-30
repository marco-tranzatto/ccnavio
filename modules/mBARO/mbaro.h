#ifndef MBARO_H
#define MBARO_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       mbaro.h
 * \brief       Barometer Module
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \ingroup     CCNAVIODEMO
 */

#include <CCLibROS.h>
#include <cc_msgs/BARORaw.h>

#include <Navio/MS5611.h>

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup CCNAVIODEMO
 *  @{
 */

using namespace CC::ROS;

namespace CC {
namespace MODULES {

class mBARO : public QROSModule
{
private:
    typedef cc_msgs::BARORaw    BAROPacket;
    static  const qreal         m_rDefaultFreq = 0.5;
protected:
    MS5611      m_Device;
    qbool       m_DeviceOk;
    BAROPacket  m_Packet;
    Publisher   m_Publiher;

public:
    mBARO();
    mBARO(QString sIMUID);

    qbool isReady() const;

protected:
    void runningCode();
};
}
}

/** @}*/

#endif // MBARO_H
