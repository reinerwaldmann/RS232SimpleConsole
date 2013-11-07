#-------------------------------------------------
#
# Project created by QtCreator 2013-10-30T12:11:53
#
#-------------------------------------------------

include(qextserialport-1.2beta2/src/qextserialport.pri)
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RS232SimpleConsole
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    DeviceManagerIzluchatel/devicewidget.cpp \
    DeviceManagerIzluchatel/devicemanagerizluchatelui.cpp \
    DeviceManagerIzluchatel/devicemanagerizluchatel.cpp \
    DeviceManagerIzluchatel/devicelan.cpp \
    DeviceManagerIzluchatel/device.cpp

HEADERS  += mainwindow.h \
    DeviceManagerIzluchatel/devicewidget.h \
    DeviceManagerIzluchatel/devicemanagerizluchatelui.h \
    DeviceManagerIzluchatel/devicemanagerizluchatel.h \
    DeviceManagerIzluchatel/devicelan.h \
    DeviceManagerIzluchatel/device.h

FORMS    += mainwindow.ui \
    DeviceManagerIzluchatel/devicewidget.ui \
    DeviceManagerIzluchatel/devicemanagerizluchatelui.ui
