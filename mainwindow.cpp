#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createfiledialog.h"
#include "qfont.h"
#include <QFont>
#include <QString>
#include <QMenuBar>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QByteArray>
#include <limits.h>
#include "helpdialog.h"
#include "creditdialog.h"
#include "settingsdialog.h"
#include <QCloseEvent>
#include <QList>
#include <QColorDialog>
#include <QColor>
#include <QTranslator>
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadsettings();
    ui->doubleSpinBox->setValue(12);
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->setUndoRedoEnabled(true);
    QList<QString> alignment;
    alignment <<"Linksbündig" <<"Zentriert" <<"Rechtsbündig";
    ui->comboBox->addItems(alignment);
}

MainWindow::~MainWindow()
{
    delete ui;
}
char out[127];
int i;
QString text, datei, pfad = "D:\\Dokumente\\", name = "datei.txt";
QString mylanguage, usage, savecolorchar;
bool v_checked = 0;
QColor textcolor, initial = Qt::white, color, customcolor[16];
QColorDialog::ColorDialogOptions options;

void MainWindow::loadsettings()
{
    datei = "settings.txt";
    QFile f(datei);
    QTextStream in(&f);
    openf:if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        char* dataf = new char[text.length() + 1];
        char outs[2] = ";";
        strcpy(dataf, text.toLatin1().data());

        pfad = strtok(dataf, outs);
        mylanguage = strtok(NULL, outs);
        usage = strtok(NULL, outs);
        for(i= 0; i < 16; i++)
        {
            customcolor[i] = strtok(NULL, outs);
            QColorDialog::setCustomColor(i, customcolor[i]);
        }
        //other Settings    setting = strtok(NULL, outs);
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        create = a.exec();
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            SettingsDialog a;
            a.exec();
            goto openf;
        }
    }
    FILE* fp;
    fp = fopen("tmp.txt", "w");
    fclose(fp);
}

void MainWindow::on_fontComboBox_currentFontChanged(const QFont &f)
    {    ui->textEdit->setFont(f);}

void MainWindow::on_checkBox_toggled(bool b_checked)
{
    if(b_checked)
        ui->textEdit->setFontWeight(QFont::Bold);

    else if(!b_checked)
        ui->textEdit->setFontWeight(QFont::Normal);
}

void MainWindow::on_checkBox_2_toggled(bool k_checked)
    {    ui->textEdit->setFontItalic(k_checked);}

void MainWindow::on_checkBox_3_toggled(bool u_checked)
    {    ui->textEdit->setFontUnderline(u_checked);}

void MainWindow::on_checkBox_4_toggled(bool d_checked)
{
    QFont font = ui->textEdit->font();
    font.setStrikeOut(d_checked);
    ui->textEdit->setFont(font);}

void MainWindow::on_doubleSpinBox_valueChanged(double arg1)
    {    ui->textEdit->setFontPointSize(arg1);}

void MainWindow::on_pushButton_clicked()        {
    if(!ui->checkBox_5->isChecked()) savef(); else savefv();}

void MainWindow::on_pushButton_2_clicked()      {
if(!ui->checkBox_5->isChecked())openf(); else openfv();}

void MainWindow::on_pushButton_4_clicked()      {
    if(!ui->checkBox_5->isChecked()) exportf(); else exportfv();}

void MainWindow::on_pushButton_3_clicked()      {    remove("tmp.txt"); qApp->quit();}

void MainWindow::openf()
{
    name = ui->lineEdit->text();
    datei = pfad + name;
    ui->label->setText(datei);
    QFile f(datei);
    QTextStream in(&f);
    openf:if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        ui->textEdit->setHtml(text);
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        create = a.exec();;
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto openf;
        }
    }
}

void MainWindow::savef()
{
    name = ui->lineEdit->text();
    datei = pfad + name;
    ui->label->setText(datei);
    QFile f(datei);
    QTextStream in(&f);
    savef:if(f.open(QIODevice::WriteOnly))
    {
        text = ui->textEdit->toPlainText();
        char* dataf = new char[text.length() + 1];
        strcpy(dataf, text.toLatin1().data());
        if(v_checked == 1)
        {
            for(i = 0; i < (text.length()+1); i++)
                dataf[i] = dataf[i]+10;
        }
        f.write(dataf, strlen(dataf));
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        create = a.exec();
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto savef;
        }
    }
}

void MainWindow::exportf()
{
    name = ui->lineEdit->text();
    datei = pfad + name;
    ui->label->setText(datei);
    QFile f(datei);
    QTextStream in(&f);
    exportf:if(f.open(QIODevice::WriteOnly))
    {
        text = ui->textEdit->toHtml();
        char* dataf = new char[text.length() + 1];
        strcpy(dataf, text.toLatin1().data());
        if(v_checked == 1)
        {
            for(i = 0; i < (text.length()+1); i++)
                dataf[i] = dataf[i];
        }
        f.write(dataf, strlen(dataf));
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        create = a.exec();
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto exportf;
        }
    }
}


void MainWindow::openfv()
{
    for(i=0;i<127;i++)
    {
        out[i] = i+127;
    }
    name = ui->lineEdit->text();
    datei = pfad + name;
    ui->label->setText(datei);
    QFile f(datei);
    QTextStream in(&f);
    openf:if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        char* textin = new char[text.length()+1];
        FILE* fp;
        char* file = new char[datei.length() + 1];
        strcpy(file, datei.toLatin1().data());
        fp = fopen(file, "r");
        fscanf(fp, "%s", textin);
        for(i = 0; i < (text.length()+1); i++)
        {
            textin[i] = textin[i] - 10;
            if(textin[i] > 127)
                textin[i] = ' ';
        }
        text = strtok(textin, out);
        ui->textEdit->setHtml(text);
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        create = a.exec();;
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto openf;
        }
        create = false;
    }
}

void MainWindow::savefv()
{
    name = ui->lineEdit->text();
    datei = pfad + name;
    ui->label->setText(datei);
    QFile f(datei);
    QTextStream in(&f);
    savef:if(f.open(QIODevice::WriteOnly))
    {
        text = ui->textEdit->toPlainText();
        char* dataf = new char[text.length() + 1];
        strcpy(dataf, text.toLatin1().data());
            for(i = 0; i < (text.length()+1); i++)
                dataf[i] = dataf[i]+10;
        f.write(dataf, strlen(dataf));
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        create = a.exec();
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto savef;
        }
        create = false;
    }
}

void MainWindow::exportfv()
{
    name = ui->lineEdit->text();
    datei = pfad + name;
    ui->label->setText(datei);
    QFile f(datei);
    QTextStream in(&f);
    exportf:if(f.open(QIODevice::WriteOnly))
    {
        text = ui->textEdit->toHtml();
        char* dataf = new char[text.length() + 1];
        strcpy(dataf, text.toLatin1().data());
            for(i = 0; i < (text.length()+1); i++)
                dataf[i] = dataf[i];
        f.write(dataf, strlen(dataf));
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        create = a.exec();
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto exportf;
        }
        create = false;
    }
}

void MainWindow::on_textEdit_textChanged()
{
//    text = ui->textEdit->toPlainText();
//    char* data = new char[text.length() + 1];
//    char* dataend = new char[text.length() + 1];
//    strcpy(data, text.toLatin1().data());
//    char add;
//    switch (data[text.length()-1]) {
//    case '(':
//        add = ')';
//        dataend = new char[text.length()+10];
//        dataend = data+')';
//        printf("%s\n", data);
//        printf("%s", dataend);
//        text = *dataend;
//        ui->textEdit->setText(text);
//        break;
//    case '[':
//        add = ']';
//        dataend = data + add;
//        text = dataend;
//        ui->textEdit->setText(text);
//        break;
//    case '{':
//        add = '}';
//        dataend = data + add;
//        text = dataend;
//        ui->textEdit->setText(text);
//        break;
//    default:
//        printf("hallo");
//        break;
//    }
}

void MainWindow::on_actionOeffnen_triggered()
{
    if(!ui->checkBox_5->isChecked())openf(); else openfv();
}

void MainWindow::on_actionExportieren_triggered()
{
    if(!ui->checkBox_5->isChecked()) exportf(); else exportfv();
}

void MainWindow::on_actionSpeichern_triggered()
{
     if(!ui->checkBox_5->isChecked()) savef(); else savefv();
}

void MainWindow::on_actionCredits_triggered()
{
    CreditDialog a;
    a.exec();
}

void MainWindow::on_actionAleitung_triggered()
{
    HelpDialog a;
    a.exec();
}

void MainWindow::on_actionSchliessen_triggered()    {    remove("tmp.txt"); qApp->quit();}

void MainWindow::on_actionEinstellungen_triggered()
{
    SettingsDialog a;
    a.exec();
}

void MainWindow::on_actionRueckg_ngig_triggered()       {    ui->textEdit->undo();}

void MainWindow::on_actionWiederherstellen_triggered()  {    ui->textEdit->redo();}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "Linksbündig")
        ui->textEdit->setAlignment(Qt::AlignLeft);
    else if(arg1 == "Zentriert")
        ui->textEdit->setAlignment(Qt::AlignHCenter);
    else if(arg1 == "Rechtsbündig")
        ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_pushButton_5_clicked()
{
    options = QColorDialog::DontUseNativeDialog;
    textcolor = QColorDialog::getColor(Qt::white, NULL, NULL, options);
    ui->textEdit->setTextColor(textcolor);
}

//CreateFileDialog has  Bugs, doesn't open sometimes
void MainWindow::savecolor()
{
    QFile f(datei);
    QTextStream in(&f);
    openf:if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        create = a.exec();;
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto openf;
        }
    }
    f.close();
    savef:if(f.open(QIODevice::WriteOnly))
    {
        char out[2] = ";";
        text = strtok(text.toLatin1().data(), out);
        text = text + ';' + strtok(NULL, out) + ';';
        QString text2 = strtok(NULL, out);
        text = text + text2 + ';';
        for(i = 0; i < 16; i++)
        {
            customcolor[i] = QColorDialog::customColor(i);
            savecolorchar = customcolor[i].name();
            text = text + savecolorchar + ';';
        }
        char* dataf = new char[text.length() + 1];
        strcpy(dataf, text.toLatin1().data());
        f.write(dataf, strlen(dataf));
    }
    else
    {
        bool create = false;
        CreateFileDialog a;
        a.exec();
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto savef;
        }
    }
}

void MainWindow::closeEvent( QCloseEvent *event)
{
    savecolor();
    remove("tmp.txt");
    QFile tmp("tmp.txt");
    datei = "settings.txt";
    QFile f(datei);
    f.close();
    if(tmp.remove())
        event->accept();
}
