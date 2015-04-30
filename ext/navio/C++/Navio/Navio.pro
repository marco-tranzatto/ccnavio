QT       -= gui

TARGET   = Navio
TEMPLATE = lib
CONFIG   += staticlib

HEADERS +=  ADS1115.h \
            MB85RC04.h \
            MS5611.h \
            SPIdev.h \
            I2Cdev.h \
            MPU9250.h \
            PCA9685.h \
            Ublox.h \
            gpio.h

SOURCES +=  ADS1115.cpp \
            MB85RC04.cpp \
            MS5611.cpp \
            Ublox.cpp \
            I2Cdev.cpp \
            MPU9250.cpp \
            PCA9685.cpp \
            gpio.cpp

QMAKE_CXXFLAGS += -Wno-unused-parameter -Wno-narrowing -Wno-unused-variable -Wno-sign-compare
