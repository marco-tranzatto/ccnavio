# ccnavio
QT5 and ROS meet Navio

Collection of drivers and examples for integrating Navio/Navio+ with ROS and QT5.

## Repository structure

### cc_msgs

ROS additional messages to handle Navio+ sensor set.

### demo

Demo software to test ROS and the implemented middleware abstraction.

### ext

External dependencies (i.e. EMLID Navio C++ library)

### include

Headers for the middleware abstraction layer, including xml, ros, math and more.

### lib

Math, ROS middleware abstraction, XML configuration handling and Programming by Contract implementation.

### modules

EMLID Navio/Navio+ ready-to-go modules including:


* mBARO: Barometer (cc_msgs::BARORaw) on Navio/Barometer
* mGPS:  GPS (cc_msgs::GPSRaw) on Navio/Gps
* mIMU:  IMU (cc_msgs::IMURaw) on Navio/Imu
* mPWM:  RGBLed (cc_msgs::RGBLed) on Navio/Led and (cc_msgs::Servo) spread over different topics named Navio/Servo1-13

## RPi2 SD image with ccnavio

Soon a Raspberry Pi 2 + Navio compatible with the ccnavio library will be released... stay tuned ;)


