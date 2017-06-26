#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_fontComboBox_currentFontChanged(const QFont &f);

    void on_checkBox_toggled(bool b_checked);

    void on_checkBox_2_toggled(bool k_checked);

    void on_checkBox_3_toggled(bool u_checked);

    void on_checkBox_4_toggled(bool d_checked);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_actionOeffnen_triggered();

    void on_actionExportieren_triggered();

    void on_actionSpeichern_triggered();

    void on_actionCredits_triggered();

    void on_actionAleitung_triggered();

    void on_actionSchliessen_triggered();

    void on_actionEinstellungen_triggered();

    void on_textEdit_textChanged();

    void on_actionRueckg_ngig_triggered();

    void on_actionWiederherstellen_triggered();

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_5_clicked();

    void on_actionSpeichern_als_triggered();

    void on_actionDrucken_triggered();

    void save();

    void open();

private:
    Ui::MainWindow *ui;
    void openf();
    void savef();
    void exportf();
    void openfv();
    void savefv();
    void exportfv();
    void loadsettings();
    void closeEvent(QCloseEvent *event);
    void savecolor();
    void inittimer();
    void print();
    void loadtheme();

};

#endif // MAINWINDOW_H
