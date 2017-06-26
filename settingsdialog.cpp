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
    usage <<tr("Büroarbeit") <<tr("Entwicklung") <<tr("Wissenschaftlich");
    ui->comboBox_2->addItems(usage);
    QList<QString> autosaveintervall;
    autosaveintervall <<"0.5 min" <<"1 min" <<"5 min" <<"10 min" << "30 min" << tr("Nie");
    ui->comboBox_3->addItems(autosaveintervall);
    QList<QString> theme;
    theme << tr("Normal") << tr("Dunkel");
    ui->comboBox_4->addItems(theme);
    load();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
QString language, colors;

void SettingsDialog::load()
{
    QString datei = "settings.txt", text, junk;
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
        ui->comboBox_3->setCurrentText((strtok(NULL, outs)));
        ui->comboBox_4->setCurrentText((strtok(NULL, outs)));
        junk = strtok(NULL, outs);
        ui->checkBox->setChecked(junk.toInt());
        colors = strtok(NULL, "_");
        //other settings
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
    QString datei = "settings.txt", text, color[16], junk;
    QFile f(datei);
    QTextStream in(&f);
    savef:if(f.open(QIODevice::WriteOnly))
    {
        if(ui->checkBox->isChecked())
            junk = '1';
        else junk = '0';
        text = (ui->lineEdit->text() + ';');
        text = (text + ui->comboBox->currentText() + ';');
        text = (text + ui->comboBox_2->currentText() + ';');
        text = (text + ui->comboBox_3->currentText() + ';');
        text = (text + ui->comboBox_4->currentText() + ';');
        text = (text + junk + ';');
        //other settings
        text = text + colors;
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
