#-------------------------------------------------
#
# Project created by QtCreator 2014-07-01T21:14:29
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = tcdstation
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    untreatedreport.cpp \
    producedreportpage.cpp \
    datagatherdialog.cpp \
    patienttracker.cpp \
    reportgenerationdialog.cpp \
    presetdiagnosisdialog.cpp \
    presetdiagnosiseditdialog.cpp \
    reportformdefinition.cpp \
    patientmodel.cpp \
    reportprintsetting.cpp \
    imagebase.cpp \
    tcdimage.cpp \
    videostreamhandler.cpp \
    getpatientinfomation.cpp


HEADERS  += mainwindow.h \
    untreatedreport.h \
    producedreportpage.h \
    datagatherdialog.h \
    patienttracker.h \
    dataformatdef.h \
    reportgenerationdialog.h \
    presetdiagnosisdialog.h \
    presetdiagnosiseditdialog.h \
    reportformdefinition.h \
    patientmodel.h \
    reportprintsetting.h \
    imagebase.h \
    tcdimage.h \
    videostreamhandler.h \
    getpatientinfomation.h

FORMS    += mainwindow.ui \
    untreatedreport.ui \
    producedreportpage.ui \
    datagatherdialog.ui \
    reportgenerationdialog.ui \
    presetdiagnosisdialog.ui \
    presetdiagnosiseditdialog.ui

RESOURCES +=

INCLUDEPATH += D:\opencv\include

LIBS += -LD:\opencv\lib

LIBS += libopencv_core243.dll\
        libopencv_highgui243.dll
#        libopencv_imgproc243


