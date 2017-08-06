#ifndef GEFILE_H
#define GEFILE_H

#include <QString>
#include <QTextEdit>

class GeFile
{
public:
    GeFile();
    GeFile(QString html);
    void sethtml(QString html);
    QString gethtml();
    void inserthtml(QString html, int position);
    void settext(QString text);
    QString gettext();
    void inserttext(QString text, int position);
    QString getdescript();
    void setdescript(QString text);
    QString getenscript();
    void setenscript(QString text);
    int length();

private:

    QTextEdit edit;
    int Length;
    QString Html, Text;
};

#endif // GEFILE_H
