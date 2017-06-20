#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <stdio.h>

QTranslator qtTranslator;
int loadlanguage()
{
    QString datei = "settings.txt", mylanguage, text, junk;
    QFile f(datei);
    QTextStream in(&f);
    if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        char* dataf = new char[text.length() + 1];
        char outs[2] = ";";
        strcpy(dataf, text.toLatin1().data());

        junk = strtok(dataf, outs);
        mylanguage = strtok(NULL, outs);
    }
#ifdef WIN32
    if(mylanguage == "Systemsprache")
        qtTranslator.load("qt_de.qm" , "translations\\"); //isn't finish
    else if(mylanguage == "Deutsch")
        qtTranslator.load("qt_de.qm", "translations\\");
    else if(mylanguage == "English")
        qtTranslator.load("qt_en.qm", "translations\\");
    else if(mylanguage == "Francais")
        qtTranslator.load("qt_fr.qm", "translations\\");
    else if(mylanguage == "")
        qtTranslator.load("qt_ru.qm", "translations\\");
    else
        return 1;
#endif
#ifndef WIN32
    if(mylanguage == "Systemsprache")
        qtTranslator.load("qt_de.qm" , "./translations/"); //isn't finish
    else if(mylanguage == "Deutsch")
        qtTranslator.load("qt_de.qm", "./translations/");
    else if(mylanguage == "English")
        qtTranslator.load("qt_en.qm", "./translations/");
    else if(mylanguage == "Francais")
        qtTranslator.load("qt_fr.qm", "./translations/");
    else if(mylanguage == "")
        qtTranslator.load("qt_ru.qm", "./translations/");
    else
        return 1;
#endif
    return 0;
}

int main(int argc, char *argv[])
{
    int languagesucces = loadlanguage();
    printf("%i", languagesucces);
    QApplication a(argc, argv);
    a.installTranslator(&qtTranslator);
    MainWindow w;
    w.show();
    bool succsess = a.exec();
    return succsess;
}

