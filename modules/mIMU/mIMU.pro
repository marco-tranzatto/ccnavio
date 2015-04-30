#-------------------------------------------------
#
# Project created by QtCreator 2014-11-08T12:09:15
#
#-------------------------------------------------

QT       += core
QT       += xml
QT       -= gui

TARGET = mIMU
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

HEADERS += \
    mimu.h

SOURCES +=  main.cpp \
            mimu.cpp

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

#REMEMBER TO GET THE LAST ccsettings.xml
xml_settings.path  = $$OUT_PWD
xml_settings.files = ccsettings.xml
INSTALLS        += xml_settings

# CUSTOM PACKETS CC_MSGS
INCLUDEPATH     += $$PWD/../../cc_msgs/msg_gen/cpp/include/

# Navio
LIBS += -L$$OUT_PWD/../../ext/navio/C++/Navio/ -lNavio
INCLUDEPATH += $$PWD/../../ext/navio/C++/
DEPENDPATH += $$PWD/../../ext/navio/C++/Navio
PRE_TARGETDEPS += $$OUT_PWD/../../ext/navio/C++/Navio/libNavio.a
