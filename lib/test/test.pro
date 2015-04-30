#-------------------------------------------------
#
# Project created by QtCreator 2014-10-04T16:22:58
#
#-------------------------------------------------

QT      += testlib core
SOURCES  =  \
            CCLibMathTest.cpp \
            main.cpp

CONFIG   += testlib
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

LIBS           += -L$$OUT_PWD/../../include/ -lCCInclude
INCLUDEPATH    += $$PWD/../../include
DEPENDPATH     += $$PWD/../../include
PRE_TARGETDEPS += $$OUT_PWD/../../include/libCCInclude.a

LIBS           += -L$$OUT_PWD/../kernel/ -lCCLibrary
INCLUDEPATH    += $$PWD/../kernel
DEPENDPATH     += $$PWD/../kernel
PRE_TARGETDEPS += $$OUT_PWD/../kernel/libCCLibrary.a

LIBS           += -llapack -lblas -larmadillo

# GCOV Option for Code Coverage
#QMAKE_CXXFLAGS  += -g -Wall -fprofile-arcs -ftest-coverage -O0  --coverage
#QMAKE_CFLAGS    += -g -Wall -fprofile-arcs -ftest-coverage -O0  --coverage
#QMAKE_LFLAGS    += -g -Wall -fprofile-arcs -ftest-coverage -O0  --coverage
#LIBS            += -lgcov   --coverage
