#-------------------------------------------------
#
# Project created by QtCreator 2018-07-18T09:24:13
#
#-------------------------------------------------

QT       += core serialport network

QT       -= gui

TARGET = GateWayClient
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mnetwork.cpp \
    mserialport.cpp \
    netprotocol.cpp \
    serialprotocol.cpp \
    raspiclient.cpp \
    dataqueue.cpp

HEADERS += \
    mnetwork.h \
    mserialport.h \
    netprotocol.h \
    serialprotocol.h \
    raspiclient.h \
    dataqueue.h
