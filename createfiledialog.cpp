#include "createfiledialog.h"
#include "ui_createfiledialog.h"
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <mainwindow.h>

CreateFileDialog::CreateFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateFileDialog)
{
    ui->setupUi(this);
    setlabel();

}

CreateFileDialog::~CreateFileDialog()
{
    delete ui;
}

void CreateFileDialog::setlabel()
{
    QString datei = "settings.txt", check = "tmp.txt";
    QFile f(datei), c(check);
    bool mainvisible =  false;

    if(c.open(QIODevice::ReadOnly))
             mainvisible = true;
    if((f.open(QIODevice::ReadOnly) || mainvisible))    {   ;  }
    else
    {
        ui->label->setText("Die Einstellungsdatei existiert nicht.\nSoll sie erstellt werden?");}
    }

void CreateFileDialog::on_buttonBox_accepted()
{
    done(1);
}

void CreateFileDialog::on_buttonBox_rejected()
{
    FILE* fp;
    fp = fopen("tmp.txt", "w");
    fclose(fp);
    done(0);
}
