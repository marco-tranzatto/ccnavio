#-------------------------------------------------
#
# Project created by QtCreator 2014-10-31T23:40:01
#
#-------------------------------------------------

QT       += core xml

QT       -= gui

TARGET = middleware_basic
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    simplemodule.cpp



LIBS            += -L$$OUT_PWD/../../include/ -lCCInclude
INCLUDEPATH     += $$PWD/../../include
DEPENDPATH      += $$PWD/../../include
PRE_TARGETDEPS  += $$OUT_PWD/../../include/libCCInclude.a

LIBS            += -L$$OUT_PWD/../../lib/kernel/ -lCCLibrary
INCLUDEPATH     += $$PWD/../../lib/kernel
DEPENDPATH      += $$PWD/../../lib/kernel
PRE_TARGETDEPS  += $$OUT_PWD/../../lib/kernel/libCCLibrary.a

# ROS
INCLUDEPATH    += /opt/ros/indigo/include
LIBS           += -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime -lroscpp_serialization

#LIBS            += -lgcov   --coverage

# CUSTOM PACKETS CC_MSGS
INCLUDEPATH     += $$PWD/../../cc_msgs/msg_gen/cpp/include/
INCLUDEPATH     += /opt/ros/indigo/share/cc_msgs/msg_gen/cpp/include/

HEADERS += \
    simplemodule.h

OTHER_FILES += \
    ccsettings.xml
