QT       -= gui
QT       += core xml

TARGET   = CCInclude
TEMPLATE = lib
CONFIG   += staticlib

HEADERS += \
    CCUnitTest.h \
    CCTypes.h \
    CCPBC.h \
    CCLibROS.h \
    CCLibXml.h \
    CCLibMath.h

# ROS
INCLUDEPATH    += /opt/ros/indigo/include
LIBS           += -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime -lroscpp_serialization
