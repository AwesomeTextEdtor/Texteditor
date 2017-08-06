#ifndef DEENSCRIPT_H
#define DEENSCRIPT_H
#include <QString>


QString enscript(QString string)
{
    char* dataf = new char[string.length() + 1];
    strcpy(dataf, string.toLatin1().data());
    for(int i = 0; i < (string.length()+1); i++)
        dataf[i] = dataf[i]+12;
    string = dataf;
    return string;
}

QString enscript(QString string, int codec)
{
    char* dataf = new char[string.length() + 1];
    strcpy(dataf, string.toLatin1().data());
    for(int i = 0; i < (string.length()+1); i++)
        dataf[i] = dataf[i]+codec;
    string = dataf;
    return string;
}

QString descript(QString string)
{
    char* dataf = new char[string.length() + 1];
    strcpy(dataf, string.toLatin1().data());
    for(int i = 0; i < (string.length()+1); i++)
        dataf[i] = dataf[i]-12;
    string = dataf;
    return string;
}

QString descript(QString string, int codec)
{
    char* dataf = new char[string.length() + 1];
    strcpy(dataf, string.toLatin1().data());
    for(int i = 0; i < (string.length()+1); i++)
        dataf[i] = dataf[i]-codec;
    string = dataf;
    return string;
}



#endif // DEENSCRIPT_H
