#-------------------------------------------------
#
# Project created by QtCreator 2017-03-08T21:34:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Texteditor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    createfiledialog.cpp \
    helpdialog.cpp \
    creditdialog.cpp \
    settingsdialog.cpp

HEADERS  += mainwindow.h \
    createfiledialog.h \
    helpdialog.h \
    creditdialog.h \
    settingsdialog.h

FORMS    += mainwindow.ui \
    createfiledialog.ui \
    helpdialog.ui \
    creditdialog.ui \
    settingsdialog.ui
