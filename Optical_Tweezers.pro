#-------------------------------------------------
#
# Project created by QtCreator 2016-12-23T10:28:10
#
#-------------------------------------------------

QT       += core gui \
         multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Optical_Tweezers
TEMPLATE = app


SOURCES += main.cpp \
    Game.cpp \
    Ball.cpp \
    Mirror.cpp \
    Light.cpp \
    Lasergenerator.cpp \
    Loading.cpp \
    Mainwindow.cpp \
    Settings.cpp \
    Win_Zone.cpp

HEADERS  += \
    Game.h \
    Ball.h \
    Mirror.h \
    Light.h \
    Lasergenerator.h \
    Settings.h \
    Mainwindow.h \
    Loading.h \
    Win_Zone.h

FORMS    += mainwindow.ui \
    loading.ui \
    settings.ui

RESOURCES += \
    res.qrc
