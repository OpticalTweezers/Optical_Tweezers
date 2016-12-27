#-------------------------------------------------
#
# Project created by QtCreator 2016-12-23T10:28:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Optical_Tweezers
TEMPLATE = app


SOURCES += main.cpp \
    Game.cpp \
    Ball.cpp \
    Mirrow.cpp \
    lasergenerator.cpp \
    light.cpp \
    mainwindow.cpp \
    loading.cpp \
    settings.cpp

HEADERS  += \
    Game.h \
    Ball.h \
    Mirrow.h \
    lasergenerator.h \
    light.h \
    mainwindow.h \
    loading.h \
    settings.h

FORMS    += mainwindow.ui \
    loading.ui \
    settings.ui

RESOURCES += \
    res.qrc
