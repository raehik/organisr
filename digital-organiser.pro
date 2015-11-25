#-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T14:38:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = digital-organiser
TEMPLATE = app

LIBS += -lsqlite3

INCLUDEPATH += $$PWD/include


SOURCES += src/main.cpp \
    src/sqlitehelper.cpp \
    src/datahandler.cpp \
    src/appointment.cpp \
    src/dbhelper.cpp \
    src/guihandler.cpp \
    src/guimainwindow.cpp \
    src/newapptdialog.cpp

HEADERS  += \
    include/datahandler.h \
    include/appointment.h \
    include/sqlitehelper.h \
    include/dbhelper.h \
    include/guihandler.h \
    include/guimainwindow.h \
    include/newapptdialog.h
