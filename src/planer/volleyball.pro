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
    itemdelegates.cpp \
    interimgames.cpp \
    crossgames.cpp \
    classementgames.cpp \
    basegamehandling.cpp \
    about.cpp \
    viewclassement.cpp \
    viewdivisions.cpp \
    viewallresults.cpp

HEADERS  += mainwindow.h \
    database.h \
    logging.h \
	ftploader.h \
    worker.h \
    qualifyinggames.h \
    calculateresults.h \
    itemdelegates.h \
    interimgames.h \
    crossgames.h \
    classementgames.h \
    basegamehandling.h \
    about.h \
    viewclassement.h \
    viewdivisions.h \
    viewallresults.h

FORMS    += mainwindow.ui \
    about.ui \
    viewclassement.ui \
    viewdivisions.ui \
    viewallresults.ui

DISTFILES += \
    resources/config.ini \
    resources/version.txt
