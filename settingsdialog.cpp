#define SETTINGSDIALOG
//#include "includes.h"

#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <string>
#include <QColorDialog>
#include <QMessageBox>

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
    theme << "Normal" << "Dark" << "Dark Fusion";
    ui->comboBox_4->addItems(theme);
    load();
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}
QString language, addColor, colors;
QColor customcolors[16];

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
        for(int i= 0; i < 16; i++)
        {
            QString addColor = strtok(NULL, outs);
            customcolors[i] = addColor;
            colors.append(addColor+";");
            QColorDialog::setCustomColor(i, customcolors[i]);
            QPixmap pixmap(10, 10);
            pixmap.fill(customcolors[i]);
            QIcon colorIcon(pixmap);
            ui->comboBox_5->addItem(colorIcon, addColor);
        }
        //other settings
    }
    else
    {
        QMessageBox messageBox;
        messageBox.addButton(QMessageBox::Yes);messageBox.addButton(QMessageBox::No);
        messageBox.setText(tr("Die Einstellungsdatei existiert nicht\nSoll sie erstellt werden?"));
        if(messageBox.exec() == QMessageBox::Yes)
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
    accept();
}

void SettingsDialog::on_buttonBox_rejected()
{
    reject();
}

void SettingsDialog::on_applyButton_clicked()
{
    save();
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
        QMessageBox messageBox;
        messageBox.addButton(QMessageBox::Yes);messageBox.addButton(QMessageBox::No);
        messageBox.setText(tr("Die Einstellungsdatei existiert nicht\nSoll sie erstellt werden?"));
        if(messageBox.exec() == QMessageBox::Yes)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            goto savef;
        }
    }
}

void SettingsDialog::on_pushButton_clicked()
{
    QColorDialog a;
    a.exec();
    ui->comboBox_5->clear();
    colors.clear();
    for(int i= 0; i < 16; i++)
    {
        customcolors[i] = QColorDialog::customColor(i);
        QString addColor = customcolors[i].name();
        colors.append(addColor+";");
        QColorDialog::setCustomColor(i, customcolors[i]);
        QPixmap pixmap(10, 10);
        pixmap.fill(customcolors[i]);
        QIcon colorIcon(pixmap);
        ui->comboBox_5->addItem(colorIcon, addColor);
    }
}

#undef SETTINGSDIALOG







