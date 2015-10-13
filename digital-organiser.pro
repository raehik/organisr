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
    src/sqlitehelper.cpp

HEADERS  += \
    include/sqlitehelper.hpp

FORMS    +=
