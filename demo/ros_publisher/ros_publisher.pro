#-------------------------------------------------
#
# Project created by QtCreator 2014-10-31T22:14:55
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ros_publisher
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

# ROS
INCLUDEPATH    += /opt/ros/indigo/include
LIBS           += -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime -lroscpp_serialization
