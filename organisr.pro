-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T14:38:28
#
#-------------------------------------------------

QT       += core gui printsupport

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = organisr
TEMPLATE = app

LIBS += -L $$PWD/lib -lSQLiteCpp -ldl -lpthread -lsqlite3

INCLUDEPATH += $$PWD/include


SOURCES += \
    src/datahandler.cpp \
    src/dbhelper.cpp \
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
    src/gnewtododialog.cpp \
    src/testcommon.cpp \
    src/testsql.cpp \
    src/testgui.cpp \
    src/datarecord.cpp \
    src/dataobject.cpp \
    src/gapptdaywidget.cpp \
    src/gwinsearchappt.cpp \
    src/gwinapptlist.cpp \
    src/gwinviewapptmonth.cpp

HEADERS  += \
    include/datahandler.h \
    include/dbhelper.h \
    include/guihandler.h \
    include/log.h \
    include/sqlitehelper.h \
    include/gmainwindow.h \
    include/gnewapptdialog.h \
    include/gwarningbox.h \
    include/gtodolistwidget.h \
    include/gwidgetprinter.h \
    include/gwinabout.h \
    include/gnewtododialog.h \
    include/testcommon.h \
    include/testsql.h \
    include/testgui.h \
    include/rectodo.h \
    include/recappt.h \
    include/datarecord.h \
    include/dataobject.h \
    include/gapptdaywidget.h \
    include/gwinsearchappt.h \
    include/gwinapptlist.h \
    include/gwinviewapptmonth.h
