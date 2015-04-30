#ifndef MPWM_H
#define MPWM_H

/*------------------------------------------------------------------------------------------------------*/
/**
 * \file:       mpwm.h
 * \brief       PWM/LED Module
 *
 * \author:     Vincenzo Calabrò <vincenzo@calabrothers.com>
 *
 * \ingroup     CCNAVIODEMO
 */


#include <CCLibROS.h>
#include <cc_msgs/RGBLed.h>
#include <cc_msgs/Servo.h>
#include <Navio/PCA9685.h>

/*------------------------------------------------------------------------------------------------------*/
/** \addtogroup CCNAVIODEMO
 *  @{
 */

#define NAVIO_PWM_CHANNELS 13
#define NAVIO_LED_R_CH      0
#define NAVIO_LED_G_CH      1
#define NAVIO_LED_B_CH      2
#define NAVIO_SERVO_CH_1    3
#define NAVIO_SERVO_CH_2    4
#define NAVIO_SERVO_CH_3    5
#define NAVIO_SERVO_CH_4    6
#define NAVIO_SERVO_CH_5    7
#define NAVIO_SERVO_CH_6    8
#define NAVIO_SERVO_CH_7    9
#define NAVIO_SERVO_CH_8    10
#define NAVIO_SERVO_CH_9    11
#define NAVIO_SERVO_CH_10   12
#define NAVIO_SERVO_CH_11   13
#define NAVIO_SERVO_CH_12   14
#define NAVIO_SERVO_CH_13   15
#define NAVIO_SERVO_MIN_PWM 1.250
#define NAVIO_SERVO_MAX_PWM 1.750
#define NAVIO_SERVO_MIN_IN  -1.0
#define NAVIO_SERVO_MAX_IN  +1.0
using namespace CC::ROS;

namespace CC {
namespace MODULES {

class mPWM : public QROSModule
{
private:
    typedef cc_msgs::RGBLed     LedPacket;
    typedef cc_msgs::Servo      ServoPacket;

    static  const qreal         m_rDefaultPwmFreq = 50.0;
protected:
    PCA9685     m_Device;
    qbool       m_DeviceOk;

    Subscriber  m_Led;
    Subscriber  m_aServo[NAVIO_PWM_CHANNELS];

private:
    void setServo(  const quint16& unChannel,
                    const ServoPacket::ConstPtr& msg);
protected:
    void onLedChange(const LedPacket::ConstPtr& msg);
    void onServoChange_1(const ServoPacket::ConstPtr& msg);
    void onServoChange_2(const ServoPacket::ConstPtr& msg);
    void onServoChange_3(const ServoPacket::ConstPtr& msg);
    void onServoChange_4(const ServoPacket::ConstPtr& msg);
    void onServoChange_5(const ServoPacket::ConstPtr& msg);
    void onServoChange_6(const ServoPacket::ConstPtr& msg);
    void onServoChange_7(const ServoPacket::ConstPtr& msg);
    void onServoChange_8(const ServoPacket::ConstPtr& msg);
    void onServoChange_9(const ServoPacket::ConstPtr& msg);
    void onServoChange_10(const ServoPacket::ConstPtr& msg);
    void onServoChange_11(const ServoPacket::ConstPtr& msg);
    void onServoChange_12(const ServoPacket::ConstPtr& msg);
    void onServoChange_13(const ServoPacket::ConstPtr& msg);
public:
    mPWM();
    mPWM(QString sGPSID);

    qbool isReady() const;

protected:
    void runningCode();
};
}
}

/** @}*/

#endif // MPWM_H
