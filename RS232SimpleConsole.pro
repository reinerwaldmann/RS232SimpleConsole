#-------------------------------------------------
#
# Project created by QtCreator 2013-10-30T12:11:53
#
#-------------------------------------------------

include(qextserialport-1.2beta2/src/qextserialport.pri)
QT       += core gui network xml

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
    DeviceManagerIzluchatel/devicers232rubin201.cpp \
    DeviceManagerIzluchatel/devicelanjerome.cpp \
    DeviceManagerIzluchatel/devicefinder.cpp \
    DeviceManagerIzluchatel/measurer.cpp \
    DeviceManagerIzluchatel/controller.cpp \
    mainwindow.cpp

HEADERS  += \
    DeviceManagerIzluchatel/devicewidget.h \
    DeviceManagerIzluchatel/devicemanagerizluchatelui.h \
    DeviceManagerIzluchatel/devicemanagerizluchatel.h \
    DeviceManagerIzluchatel/devicelan.h \
    DeviceManagerIzluchatel/device.h \
    DeviceManagerIzluchatel/devicers232.h \
    DeviceManagerIzluchatel/devicers232rubin201.h \
    DeviceManagerIzluchatel/devicelanjerome.h \
    DeviceManagerIzluchatel/devicefinder.h \
    DeviceManagerIzluchatel/measurer.h \
    DeviceManagerIzluchatel/controller.h \
    mainwindow.h

FORMS    += \
    DeviceManagerIzluchatel/devicewidget.ui \
    DeviceManagerIzluchatel/devicemanagerizluchatelui.ui \
    DeviceManagerIzluchatel/devicefinder.ui \
    mainwindow.ui
