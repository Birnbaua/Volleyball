#-------------------------------------------------
#
# Project created by QtCreator 2016-01-21T10:34:01
#
#-------------------------------------------------

QT += core
QT += gui
QT += sql
QT += network
QT += widgets

TARGET = volleyball
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
    database.cpp \
    logging.cpp \
	ftploader.cpp \
    worker.cpp \
    qualifyinggames.cpp \
    calculateresults.cpp \
    viewdivisionresults.cpp \
    itemdelegates.cpp \
    interimgames.cpp \
    crossgames.cpp \
    classementgames.cpp \
    viewclassementresults.cpp \
    basegamehandling.cpp

HEADERS  += mainwindow.h \
    database.h \
    logging.h \
	ftploader.h \
    worker.h \
    qualifyinggames.h \
    calculateresults.h \
    viewdivisionresults.h \
    itemdelegates.h \
    interimgames.h \
    crossgames.h \
    classementgames.h \
    viewclassementresults.h \
    basegamehandling.h

FORMS    += mainwindow.ui \
    viewdivisionresults.ui \
    viewclassementresults.ui