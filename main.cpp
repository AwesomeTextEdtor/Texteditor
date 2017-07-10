#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <stdio.h>

QTranslator MyTranslator, QtTranslator;
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
    {MyTranslator.load("qt_de.qm" , "translations\\");} //isn't finish
    else if(mylanguage == "Deutsch")
        {MyTranslator.load("tr_de.qm", "translations\\"); QtTranslator.load("qt_de.qm", "translations\\");}
    else if(mylanguage == "English")
        {MyTranslator.load("tr_en.qm", "translations\\"); QtTranslator.load("qt_en.qm", "translations\\");}
    else if(mylanguage == "Francais")
        {MyTranslator.load("tr_fr.qm", "translations\\"); QtTranslator.load("qt_fr.qm", "translations\\");}
    else if(mylanguage == "")
        {MyTranslator.load("tr_de.qm", "translations\\"); QtTranslator.load("qt_de.qm", "translations\\");}
    else
        return 1;
#endif
#ifndef WIN32
    if(mylanguage == "Systemsprache")
        MyTranslator.load("qt_de.qm" , "./translations/"); //isn't finish
    else if(mylanguage == "Deutsch")
        MyTranslator.load("qt_de.qm", "./translations/");
    else if(mylanguage == "English")
        MyTranslator.load("qt_en.qm", "./translations/");
    else if(mylanguage == "Francais")
        MyTranslator.load("qt_fr.qm", "./translations/");
    else if(mylanguage == "")
        MyTranslator.load("qt_de.qm", "./translations/");
    else
        return 1;
#endif
    return 0;
}

int main(int argc, char *argv[])
{
    int languagesucces = loadlanguage();
    QApplication a(argc, argv);
    a.installTranslator(&MyTranslator);
    a.installTranslator(&QtTranslator);
    MainWindow w;
    w.show();
    bool succsess = a.exec();
    return (succsess+(languagesucces*2));
}
