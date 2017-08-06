#include "gefile.h"

QString enscriptg(QString string, int codec)
{
    char* dataf = new char[string.length() + 1];
    strcpy(dataf, string.toLatin1().data());
    for(int i = 0; i < (string.length()+1); i++)
        dataf[i] = dataf[i]+codec;
    string = dataf;
    return string;
}

QString descriptg(QString string, int codec)
{
    char* dataf = new char[string.length() + 1];
    strcpy(dataf, string.toLatin1().data());
    for(int i = 0; i < (string.length()+1); i++)
        dataf[i] = dataf[i]-codec;
    string = dataf;
    return string;
}

GeFile::GeFile()
{

}

GeFile::GeFile(QString html)
{
    Html = html;
    edit.setHtml(html);
    Text = edit.toPlainText();
}

void GeFile::sethtml(QString html)
{
    Html = html;
    edit.setHtml(html);
    Text = edit.toPlainText();
}

QString GeFile::gethtml()
{
    return Html;
}

void GeFile::inserthtml(QString html, int position)
{
    edit.textCursor().setPosition(position, QTextCursor::MoveAnchor);
    edit.textCursor().insertHtml(html);
    Html = edit.toHtml();
    Text = edit.toPlainText();
}

void GeFile::settext(QString text)
{
    edit.setPlainText(text);
    Html = edit.toHtml();
    Text = text;
}

QString GeFile::gettext()
{
    return Text;
}

void GeFile::inserttext(QString text, int position)
{
    edit.textCursor().setPosition(position, QTextCursor::MoveAnchor);
    edit.textCursor().insertText(text);
    Text = edit.toPlainText();
}

QString GeFile::getdescript()
{
    return Text;
}

void GeFile::setdescript(QString text)
{
    settext(text);
}

QString GeFile::getenscript()
{
    QString enscripted;
    enscripted = enscriptg(Text, 5);
    return enscripted;
}

void GeFile::setenscript(QString text)
{
    Text = descriptg(text, 5);
}

int GeFile::length()
{
    return Text.length();
}




