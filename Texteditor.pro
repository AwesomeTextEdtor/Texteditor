#-------------------------------------------------
#
# Project created by QtCreator 2017-08-19T16:43:19
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Texteditor_2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp\
        gefile.cpp \
    settingsdialog.cpp \
    tabledialog.cpp \
    linkdialog.cpp \
    syntaxhighlighter.cpp

HEADERS += \
        mainwindow.h\
        gefile.h\
        deenscript.h \
    settingsdialog.h \
    tabledialog.h \
    linkdialog.h\
    syntaxhighlighter.h

FORMS += \
        mainwindow.ui \
    settingsdialog.ui \
    tabledialog.ui \
    linkdialog.ui

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
    README.md
