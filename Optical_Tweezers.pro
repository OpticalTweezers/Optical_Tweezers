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
CONFIG += ordered

SOURCES += main.cpp \
    Settings.cpp \
    Game.cpp \
    Ball.cpp \
    Mirror.cpp \
    Light.cpp \
    Lasergenerator.cpp \
    Loading.cpp \
    Mainwindow.cpp \
    Win_Zone.cpp \
    Convex_Mirror.cpp \
    Concave_Mirror.cpp \
    Convex_Lens.cpp \
    Concave_Lens.cpp \
    Wall.cpp \
    Biprism.cpp\
    Win_dialog.cpp \
    Fail_dialog.cpp \
    game2.cpp \
    game3.cpp \
    game4.cpp \
    game5.cpp \
    game6.cpp \
    game7.cpp \
    game8.cpp \
    game9.cpp \
    game10.cpp \
    game11.cpp \
    game12.cpp



HEADERS  += \
    Settings.h \
    Game.h \
    Ball.h \
    Mirror.h \
    Light.h \
    Lasergenerator.h \
    Mainwindow.h \
    Loading.h \
    Win_Zone.h \
    Convex_Mirror.h \
    Concave_Mirror.h \
    Convex_Lens.h \
    Concave_Lens.h \
    Wall.h \
    Biprism.h\
    Win_dialog.h \
    Fail_dialog.h \
    game2.h \
    game3.h \
    game4.h \
    game5.h \
    game6.h \
    game7.h \
    game8.h \
    game9.h \
    game10.h \
    game11.h \
    game12.h



FORMS    += mainwindow.ui \
    loading.ui \
    settings.ui \
    Win_dialog.ui \
    Fail_dialog.ui

RESOURCES += \
    res.qrc
