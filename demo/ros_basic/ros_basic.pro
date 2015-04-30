#-------------------------------------------------
#
# Project created by QtCreator 2014-10-31T21:42:37
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ros_basic
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp

# ROS
INCLUDEPATH    += /opt/ros/indigo/include
LIBS           += -L/opt/ros/indigo/lib -Wl,-rpath,/opt/ros/indigo/lib -lroscpp -lrosconsole -lrostime
