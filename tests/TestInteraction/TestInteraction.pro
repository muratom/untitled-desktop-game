QT += testlib
QT -= gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

VPATH += ../../udg

# include the classes from the main project:
include(../../udg/udg.pri)
INCLUDEPATH += ../../udg/

SOURCES += tst_testinteraction.cpp

DISTFILES +=

RESOURCES +=
