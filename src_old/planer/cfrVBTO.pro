#-------------------------------------------------
#
# Project created by QtCreator 2015-02-19T21:05:32
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cfrVBTO
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    view_division_results.cpp \
    view_all_results.cpp \
    view_final_results.cpp

HEADERS  += mainwindow.h \
    settings.h \
    vorrunde.h \
    calculate.h \
    zwischenrunde.h \
    kreuzspiele.h \
    platzspiele.h \
    view_division_results.h \
    view_all_results.h \
    logging_v1.3.h \
    itemdelegates_v1.2.h \
    view_final_results.h \
    database_v1.3.h

FORMS    += mainwindow.ui \
    view_division_results.ui \
    view_all_results.ui \
    view_final_results.ui

DISTFILES += \
    resources/data.sqlite \
    resources/mikasa.jpg
