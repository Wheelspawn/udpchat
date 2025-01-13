TEMPLATE = app
TARGET = UDPChat

QT = core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

SOURCES += \
    main.cpp \
    peer.cpp

HEADERS += \
    peer.h
