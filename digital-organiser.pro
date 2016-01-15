-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T14:38:28
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = digital-organiser
TEMPLATE = app

LIBS += -L $$PWD/lib -lSQLiteCpp -ldl -lpthread -lsqlite3

INCLUDEPATH += $$PWD/include


SOURCES += \
    src/appointment.cpp \
    src/datahandler.cpp \
    src/dbhelper.cpp \
    src/dbobject.cpp \
    src/guihandler.cpp \
    src/log.cpp \
    src/main.cpp \
    src/sqlitehelper.cpp \
    src/gwinabout.cpp \
    src/gmainwindow.cpp \
    src/gnewapptdialog.cpp \
    src/gwarningbox.cpp \
    src/gtodolistwidget.cpp \
    src/gwidgetprinter.cpp \
    src/gnewtododialog.cpp

HEADERS  += \
    include/appointment.h \
    include/datahandler.h \
    include/dbhelper.h \
    include/dbobject.h \
    include/guihandler.h \
    include/log.h \
    include/sqlitehelper.h \
    include/gmainwindow.h \
    include/gnewapptdialog.h \
    include/gwarningbox.h \
    include/gtodolistwidget.h \
    include/gwidgetprinter.h \
    include/gwinabout.h \
    include/gnewtododialog.h
