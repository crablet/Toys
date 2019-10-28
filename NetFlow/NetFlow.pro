#-------------------------------------------------
#
# Project created by QtCreator 2019-05-17T20:57:53
#
#-------------------------------------------------

QT       += core gui charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetFlow
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++17

DEFINES += TINS_STATIC

INCLUDEPATH += $$quote("C:\Program Files\WpdPack\Include") \
               $$quote("C:\Program Files\libtins-x64\release\libtins\include")

LIBS += $$quote("C:\Program Files\WpdPack\Lib\x64\wpcap.lib") \
        $$quote("C:\Program Files\WpdPack\Lib\x64\Packet.lib") \
        $$quote("C:\Program Files\libtins-x64\release\libtins\lib\tins.lib") \
        Iphlpapi.lib \
        Ws2_32.lib

SOURCES += \
        main.cpp \
        netflow.cpp \
    topbarwidget.cpp \
    startwindow.cpp \
    analysiswindow.cpp \
    capturerecordwindow.cpp \
    netflowsniffer.cpp

HEADERS += \
        netflow.h \
    topbarwidget.h \
    startwindow.h \
    analysiswindow.h \
    capturerecordwindow.h \
    netflowsniffer.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
