#-------------------------------------------------
#
# Project created by QtCreator 2014-10-31T23:40:01
#
#-------------------------------------------------

QT       -= gui

TARGET    = AHRS
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += AHRS.cpp
HEADERS += AHRS.hpp

LIBS += -L$$OUT_PWD/../../Navio/ -lNavio
INCLUDEPATH += $$PWD/../../
DEPENDPATH += $$PWD/../../Navio
PRE_TARGETDEPS += $$OUT_PWD/../../Navio/libNavio.a

QMAKE_CXXFLAGS += -Wno-missing-field-initializers
