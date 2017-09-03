#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QSettings>
#include <QMainWindow>

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    void setSettings(QSettings *Settings, QMainWindow *Mainwindow);
    QMainWindow *mainwindow;

private slots:
    void on_buttonAccept_clicked();

    void on_buttonApply_clicked();

    void on_buttonChancel_clicked();

    void on_buttonEditColors_clicked();

private:
    Ui::SettingsDialog *ui;
    QSettings *settings;
};

#endif // SETTINGSDIALOG_H
