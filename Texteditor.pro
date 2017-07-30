#-------------------------------------------------
#
# Project created by QtCreator 2017-03-08T21:34:14
#
#-------------------------------------------------

CODECFORTR = UTF-8
QT       += core gui
QT       += printsupport

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
    settingsdialog.h \
    includes.h

FORMS    += mainwindow.ui \
    createfiledialog.ui \
    helpdialog.ui \
    creditdialog.ui \
    settingsdialog.ui

RESOURCES += \
    resources.qrc

TRANSLATIONS += \
    tr_en.ts \
    tr_de.ts \
    tr_fr.ts \
    tr_ru.ts

OTHER_FILES += \
    tr_en.ts \
    tr_de.ts \
    tr_fr.ts \
    tr_ru.ts \
    notes.txt \
    readme.md

