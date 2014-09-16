#-------------------------------------------------
#
# Project created by QtCreator 2014-09-15T13:23:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#QMAKE_LFLAGS +=/MANIFESTUAC:"level='requireAdministrator'uiAccess='false'"）
# TARGET = ../../low_mac_test/app/TransData
TARGET = TransData
TEMPLATE = app


SOURCES += main.cpp\
        hardconfigure.cpp \
    outputdialog.cpp \
    myscrollbar.cpp

HEADERS  += hardconfigure.h \
    outputdialog.h \
    myscrollbar.h

FORMS    += hardconfigure.ui
