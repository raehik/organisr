-------------------------------------------------
#
# Project created by QtCreator 2015-10-12T14:38:28
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = digital-organiser
TEMPLATE = app

LIBS += -L $$PWD/lib -lsqlite3 -lSQLiteCpp

INCLUDEPATH += $$PWD/include


SOURCES += \
    src/appointment.cpp \
    src/datahandler.cpp \
    src/dbhelper.cpp \
    src/dbobject.cpp \
    src/guihandler.cpp \
    src/guimainwindow.cpp \
    src/log.cpp \
    src/main.cpp \
    src/newapptdialog.cpp \
    src/sqlitehelper.cpp \
    src/warningbox.cpp \

HEADERS  += \
    include/appointment.h \
    include/datahandler.h \
    include/dbhelper.h \
    include/dbobject.h \
    include/guihandler.h \
    include/guimainwindow.h \
    include/log.h \
    include/newapptdialog.h \
    include/sqlitehelper.h \
    include/warningbox.h \
