QT += testlib
QT -= gui
CONFIG += qt warn_on depend_includepath testcase

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

VPATH += ../../udg

# include the classes from the main project:
include(../../udg/udg.pri)
INCLUDEPATH += ../../udg/

TEMPLATE = app

SOURCES +=  tst_testmove.cpp
