#-------------------------------------------------
#
# Project created by QtCreator 2014-10-04T16:16:16
#
#-------------------------------------------------

QT       -= gui
QT       += xml
QT       += core

TARGET   =  CCLibrary
TEMPLATE =  lib
CONFIG   += staticlib

SOURCES  += \
    CCPBC.cpp \
    CCLibROS.cpp \
    CCLibXml.cpp \
    CCLibMath.cpp

LIBS           += -L$$OUT_PWD/../../include/ -lCCInclude
INCLUDEPATH    += $$PWD/../../include
DEPENDPATH     += $$PWD/../../include
PRE_TARGETDEPS += $$OUT_PWD/../../include/libCCInclude.a

# GCOV Option for Code Coverage
#QMAKE_CXXFLAGS  += -g -Wall -fprofile-arcs -ftest-coverage -O0  --coverage
#QMAKE_CFLAGS    += -g -Wall -fprofile-arcs -ftest-coverage -O0  --coverage
#QMAKE_LFLAGS    += -g -Wall -fprofile-arcs -ftest-coverage -O0  --coverage
#LIBS            += -lgcov   --coverage

# ROS
INCLUDEPATH    += /opt/ros/indigo/include
LIBS           += -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime -lroscpp_serialization

# ROS in Raspberry is affected by this warning:
# QMAKE_CXXFLAGS += -Wno-unused-variable

