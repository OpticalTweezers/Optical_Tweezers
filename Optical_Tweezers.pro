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
    Mirror.cpp \
    Light.cpp \
    Lasergenerator.cpp \
    Loading.cpp \
    Mainwindow.cpp \
    Settings.cpp \
    Win_Zone.cpp \
    Convex_Mirror.cpp \
    Concave_Mirror.cpp \
    Convex_Lens.cpp \
    Concave_Lens.cpp \
    Wall.cpp \
    Biprism.cpp

HEADERS  += \
    Game.h \
    Ball.h \
    Mirror.h \
    Light.h \
    Lasergenerator.h \
    Settings.h \
    Mainwindow.h \
    Loading.h \
    Win_Zone.h \
    Convex_Mirror.h \
    Concave_Mirror.h \
    Convex_Lens.h \
    Concave_Lens.h \
    Wall.h \
    Biprism.h

FORMS    += mainwindow.ui \
    loading.ui \
    settings.ui

RESOURCES += \
    res.qrc
