#-------------------------------------------------
#
# Project created by QtCreator 2013-10-30T12:11:53
#
#-------------------------------------------------

include(qextserialport-1.2beta2/src/qextserialport.pri)
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RS232SimpleConsole
TEMPLATE = app


SOURCES += main.cpp\
    DeviceManagerIzluchatel/devicewidget.cpp \
    DeviceManagerIzluchatel/devicemanagerizluchatelui.cpp \
    DeviceManagerIzluchatel/devicemanagerizluchatel.cpp \
    DeviceManagerIzluchatel/devicelan.cpp \
    DeviceManagerIzluchatel/device.cpp \
    DeviceManagerIzluchatel/devicers232.cpp \
    principalwindow.cpp \
    DeviceManagerIzluchatel/devicers232rubin201.cpp \
    DeviceManagerIzluchatel/devicelanjerome.cpp \
    DeviceManagerIzluchatel/devicefinder.cpp

HEADERS  += \
    DeviceManagerIzluchatel/devicewidget.h \
    DeviceManagerIzluchatel/devicemanagerizluchatelui.h \
    DeviceManagerIzluchatel/devicemanagerizluchatel.h \
    DeviceManagerIzluchatel/devicelan.h \
    DeviceManagerIzluchatel/device.h \
    DeviceManagerIzluchatel/devicers232.h \
    principalwindow.h \
    DeviceManagerIzluchatel/devicers232rubin201.h \
    DeviceManagerIzluchatel/devicelanjerome.h \
    DeviceManagerIzluchatel/devicefinder.h

FORMS    += \
    DeviceManagerIzluchatel/devicewidget.ui \
    DeviceManagerIzluchatel/devicemanagerizluchatelui.ui \
    principalwindow.ui \
    DeviceManagerIzluchatel/devicefinder.ui
