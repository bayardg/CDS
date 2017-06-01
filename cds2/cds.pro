QT += core
QT -= gui
QT += widgets
QT += charts

CONFIG += c++11

TARGET = cds
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    fenetre.cpp \
    main.cpp \
    mainFenetre.cpp \
    parse.cpp \
    table.cpp \
    tableau.cpp \
    themewidget.cpp

HEADERS += \
    fenetre.h \
    mainFenetre.h \
    parse.h \
    table.h \
    tableau.h \
    themewidget.h
