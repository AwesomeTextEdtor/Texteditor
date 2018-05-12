#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include <QLibraryInfo>
#include <QString>
#include <QTextStream>
#include <QStyle>
#include <QStyleFactory>
#include <QStyleOption>
#include <QTranslator>
#include <QDebug>
#include <QProcess>


QString theme, language;
QTranslator MyTranslator, QtTranslator;

int loadlanguage()
{
    qDebug()<<language;
#ifdef WIN32
    if(language == "Systemsprache")
    {QtTranslator.load("qt_de.qm" , "translations\\");} //isn't finish
    else if(language == "Deutsch")
        {MyTranslator.load("tr_de.qm", "translations\\"); QtTranslator.load("qt_de.qm", "translations\\");}
    else if(language == "English")
        {MyTranslator.load("tr_en.qm", "translations\\"); QtTranslator.load("qt_en.qm", "translations\\");}
    else if(language == "Francais")
        {MyTranslator.load("tr_fr.qm", "translations\\"); QtTranslator.load("qt_fr.qm", "translations\\");}
    else
        {MyTranslator.load("tr_de.qm", "translations\\"); QtTranslator.load("qt_de.qm", "translations\\");}

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

QPalette loadpalette()
{
    QPalette palette;
    if(theme == "Dark")
    {
        palette = QPalette(QColor(60,60,60));
        palette.setColor(QPalette::Base, QColor(120,120,120));
        palette.setColor(QPalette::Text, Qt::black);
    }
    else if(theme == "Dark Fusion")
    {
        palette.setColor(QPalette::Window, QColor(53,53,53));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(25,25,25));
        palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(53,53,53));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        palette.setColor(QPalette::Link, QColor(42, 130, 218));
        palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
        palette.setColor(QPalette::HighlightedText, Qt::black);
    }
    else if(theme == "Cusis")
    {
        palette.setColor( QPalette::WindowText, QColor( 240, 240, 240 ) );
        palette.setColor( QPalette::Base, QColor( 128, 128, 128 ) );
        palette.setColor( QPalette::Base, QColor( 0, 0, 0 ) );
        palette.setColor( QPalette::Shadow, QColor( 0, 0, 0 ) );
        palette.setColor( QPalette::ButtonText, QColor( 255, 255, 255 ) );
        palette.setColor( QPalette::BrightText, QColor( 0, 255, 0 ) );
        palette.setColor( QPalette::Highlight, QColor( 224, 224, 224 ) );
        palette.setColor( QPalette::HighlightedText, QColor( 0, 0, 0 ) );
        palette.setColor( QPalette::Background, QColor( 21, 21, 21 ) );
        palette.setColor( QPalette::Text, QColor( 255, 255, 255 ) );
        palette.setColor( QPalette::Button, QColor( 66, 66, 66 ) );
    }
    return palette;
}

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);
    QList<QString> arguments;
    for(int i = 0; i < argc; i++)
        arguments.append(QString(argv[i]));
    qDebug()<<arguments;
    QSettings *settings = new QSettings("Galaxyqasar", "Texteditor");
    settings->beginGroup("Mainwindow");
    theme = settings->value("theme", "Normal").toString();
    language = settings->value("language", "Deutsch").toString();
    settings->endGroup();
    loadlanguage();
    QApplication a(argc, argv);
    a.installTranslator(&MyTranslator);
    a.installTranslator(&QtTranslator);
    MainWindow w;
    if(theme == "Dark Fusion")
    {
        a.setStyle(QStyleFactory::create("Fusion"));
        a.setStyleSheet("QToolTip { color: #ffffff; background-color: #2a82da; border: 1px solid white; }");
    }
    a.setPalette(loadpalette());
    if(arguments.size() >1){
        if(QFile(arguments.at(1)).exists())
            w.openFile(arguments.at(1));
        if(arguments.contains("-c"))
            w.loadCompilers(arguments.at(arguments.indexOf("-c")+1));
    }
    w.show();
    bool succsess = a.exec();
    return succsess;
}

