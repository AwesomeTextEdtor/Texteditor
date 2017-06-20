#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <string>
#include "createfiledialog.h"
#include <QColorDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    QList<QString> mylanguage;
    mylanguage <<"Deutsch" <<"English" <<"Francais" <<"Systemsprache";
    ui->comboBox->addItems(mylanguage);
    QList<QString> usage;
    usage <<"Büroarbeit" <<"Entwicklung" <<"Wissenschaftlich";
    ui->comboBox_2->addItems(usage);
    load();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
QString language;

void SettingsDialog::load()
{
    QString datei = "settings.txt", text;
    QFile f(datei);
    QTextStream in(&f);
    openf:if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        char* textchar = new char[text.length()+1];
        strcpy(textchar, text.toLatin1().data());
        char outs[2] = ";";
        ui->lineEdit->setText(strtok(textchar, outs));
        ui->comboBox->setCurrentText((strtok(NULL, outs)));
        ui->comboBox_2->setCurrentText((strtok(NULL, outs)));
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


void SettingsDialog::on_buttonBox_accepted()
{
    save();
}

void SettingsDialog::on_buttonBox_rejected()
{

}

void SettingsDialog::save()
{
    QString datei = "settings.txt", text, color[16];
    QFile f(datei);
    QTextStream in(&f);
    savef:if(f.open(QIODevice::WriteOnly))
    {
        text = (ui->lineEdit->text() + ';');
        text = (text + ui->comboBox->currentText() + ';');
        text = (text + ui->comboBox_2->currentText() + ';');
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
