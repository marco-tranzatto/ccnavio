#include "mpwm.h"
#include <CCLibMath.h>

using namespace CC::MATH;
using namespace CC::ROS;
using namespace CC::MODULES;

void mPWM::setServo(const quint16 &unChannel,
                    const cc_msgs::Servo::ConstPtr &msg)
{
    qreal rChValue;
    qreal rChMin    = NAVIO_SERVO_MIN_IN;
    qreal rChMax    = NAVIO_SERVO_MAX_IN;
    qreal rPwmMin   = NAVIO_SERVO_MIN_PWM;
    qreal rPwmMax   = NAVIO_SERVO_MAX_PWM;

    if (msg->enabled == false)  { return; }

    if (msg->custom_value == true) {
        if (msg->min_value < msg->max_value) {
            rChMin = msg->min_value;
            rChMax = msg->max_value;
        }
    }

    if (msg->custom_pwm_ms == true) {
        if (msg->min_pwm_ms < msg->max_pwm_ms) {
            rPwmMin = msg->min_pwm_ms;
            rPwmMax = msg->max_pwm_ms;
        }
    }

    rChValue = sat(msg->value,  rChMin, rChMax);
    rChValue = remap(rChValue,  rChMin, rChMax, rPwmMin, rPwmMax);

    m_Device.setPWMmS(unChannel, rChValue);
}

void mPWM::onLedChange(const cc_msgs::RGBLed::ConstPtr &msg)
{
    qreal    rRed,  rGreen,  rBlue;
    quint16 unRed, unGreen, unBlue;

    rRed    = sat(msg->red, 0.0, 1.0);
    rGreen  = sat(msg->green, 0.0, 1.0);
    rBlue   = sat(msg->blue, 0.0, 1.0);

    unRed     = (quint16) remap(rRed,   0.0, 1.0, 0, 4095.0);
    unGreen   = (quint16) remap(rGreen, 0.0, 1.0, 0, 4095.0);
    unBlue    = (quint16) remap(rBlue,  0.0, 1.0, 0, 4095.0);

    m_Device.setPWM(NAVIO_LED_R_CH, unRed);
    m_Device.setPWM(NAVIO_LED_G_CH, unGreen);
    m_Device.setPWM(NAVIO_LED_B_CH, unBlue);
}

void mPWM::onServoChange_1(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_1, msg);
}

void mPWM::onServoChange_2(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_2, msg);
}

void mPWM::onServoChange_3(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_3, msg);
}

void mPWM::onServoChange_4(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_4, msg);
}

void mPWM::onServoChange_5(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_5, msg);
}

void mPWM::onServoChange_6(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_6, msg);
}

void mPWM::onServoChange_7(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_7, msg);
}

void mPWM::onServoChange_8(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_8, msg);
}

void mPWM::onServoChange_9(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_9, msg);
}

void mPWM::onServoChange_10(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_10, msg);
}

void mPWM::onServoChange_11(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_11, msg);
}

void mPWM::onServoChange_12(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_12, msg);
}

void mPWM::onServoChange_13(const ServoPacket::ConstPtr &msg)
{
    setServo(NAVIO_SERVO_CH_13, msg);
}

mPWM::mPWM() :
    QROSModule("mPWM"),
    m_Device(),
    m_DeviceOk(false)
{

    m_Led        = subscribe("Navio/Led",       this, &mPWM::onLedChange);
    m_aServo[0]  = subscribe("Navio/Servo1",    this, &mPWM::onServoChange_1);
    m_aServo[1]  = subscribe("Navio/Servo2",    this, &mPWM::onServoChange_2);
    m_aServo[2]  = subscribe("Navio/Servo3",    this, &mPWM::onServoChange_3);
    m_aServo[3]  = subscribe("Navio/Servo4",    this, &mPWM::onServoChange_4);
    m_aServo[4]  = subscribe("Navio/Servo5",    this, &mPWM::onServoChange_5);
    m_aServo[5]  = subscribe("Navio/Servo6",    this, &mPWM::onServoChange_6);
    m_aServo[6]  = subscribe("Navio/Servo7",    this, &mPWM::onServoChange_7);
    m_aServo[7]  = subscribe("Navio/Servo8",    this, &mPWM::onServoChange_8);
    m_aServo[8]  = subscribe("Navio/Servo9",    this, &mPWM::onServoChange_9);
    m_aServo[9]  = subscribe("Navio/Servo10",   this, &mPWM::onServoChange_10);
    m_aServo[10] = subscribe("Navio/Servo11",   this, &mPWM::onServoChange_11);
    m_aServo[11] = subscribe("Navio/Servo12",   this, &mPWM::onServoChange_12);
    m_aServo[12] = subscribe("Navio/Servo13",   this, &mPWM::onServoChange_13);

    m_Device.initialize();
    m_Device.setFrequency(m_rDefaultPwmFreq);

    m_DeviceOk   = true;
    qDebug() << "mPWM::mPWM() Module Initialized(" << m_DeviceOk << ")";
}

qbool mPWM::isReady() const
{
    return m_DeviceOk;
}

void mPWM::runningCode()
{
    if (m_DeviceOk == false) {
        qDebug() << "mPWM::runningCode() ERROR: Module is not properly initialized";
        this->stop();
    }
    /* Module will stay alive and trigger new events */
}
