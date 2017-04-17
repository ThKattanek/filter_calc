#-------------------------------------------------
#
# Project created by QtCreator 2016-12-23T08:48:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FilterCalc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    wave_buffer_class.cpp \
    qcustomplot/qcustomplot.cpp \
    osc_class.cpp

HEADERS  += mainwindow.h \
    wave_buffer_class.h \
    qcustomplot/qcustomplot.h \
    osc_class.h

FORMS    += mainwindow.ui

LIBS += -lfftw3
