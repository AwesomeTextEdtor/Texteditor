#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QColorDialog>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    mainwindow = new QMainWindow;
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::setSettings(QSettings *Settings, QMainWindow *Mainwindow)
{
    settings = Settings;
    mainwindow = Mainwindow;
    settings->beginGroup("Mainwindow");
    ui->lineEditPath->setText(settings->value("path","fehler").toString());
    ui->comboBoxLanguage->setCurrentText(settings->value("language", "English").toString());
    ui->comboBoxUsage->setCurrentText(settings->value("usage", "Büroarbeit").toString());
    ui->checkBoxAutocomplete->setChecked(settings->value("autocomplete", false).toBool());
    ui->comboBoxAutosave->setCurrentText(settings->value("autosave", "Nie").toString());
    ui->comboBoxTheme->setCurrentText(settings->value("theme", "standart").toString());
    ui->comboBoxColors->addItems(settings->value("colors").toStringList());
    settings->endGroup();
    QPixmap pixmap(10,10);
    for(int i=0;i<16;i++){
        pixmap.fill(QColor(ui->comboBoxColors->itemText(i)));
        ui->comboBoxColors->setItemIcon(i, QIcon(pixmap));
    }
}

void SettingsDialog::on_buttonAccept_clicked()
{
    accept();
}

void SettingsDialog::on_buttonApply_clicked()
{
    QStringList tmp;
    for(int i=0;i<ui->comboBoxColors->count();i++)
        tmp<<ui->comboBoxColors->itemText(i);
    settings->beginGroup("Mainwindow");
    settings->setValue("path", ui->lineEditPath->text());
    settings->setValue("language", ui->comboBoxLanguage->currentText());
    settings->setValue("usage", ui->comboBoxUsage->currentText());
    settings->setValue("autocomplete", ui->checkBoxAutocomplete->isChecked());
    settings->setValue("theme", ui->comboBoxTheme->currentText());
    settings->setValue("colors", tmp);
    settings->endGroup();
}

void SettingsDialog::on_buttonChancel_clicked()
{
    reject();
}

void SettingsDialog::on_buttonEditColors_clicked()
{
    QStringList tmp;
    QColorDialog::ColorDialogOptions options = QColorDialog::DontUseNativeDialog;
    QColorDialog a;
    a.setOptions(options);
    a.exec();
    QColor customcolor[16];
    ui->comboBoxColors->clear();
    for(int i= 0; i < 16; i++)
    {
        customcolor[i] = QColorDialog::customColor(i);
        QString addColor = customcolor[i].name();
        QColorDialog::setCustomColor(i, customcolor[i]);
        QPixmap pixmap(10, 10);
        pixmap.fill(customcolor[i]);
        QIcon colorIcon(pixmap);
        ui->comboBoxColors->addItem(colorIcon, addColor);
        tmp<<addColor;
    }
    settings->beginGroup("Mainwindow");
    settings->setValue("colors", tmp);
    settings->endGroup();
}
