#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextDocument>
#include <QPrinter>
#include <syntaxhighlighter.h>

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
    void save();
    void open();
    void printpreview(QPrinter *printer);
    void on_checkBox_toggled(bool b_checked);
    void on_checkBox_2_toggled(bool k_checked);
    void on_checkBox_3_toggled(bool u_checked);
    void on_checkBox_4_toggled(bool d_checked);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_actionBild_triggered();
    void on_actionListe_triggered();
    void on_actionTabelle_triggered();
    void on_actionOeffnen_triggered();
    void on_actionDrucken_triggered();
    void on_actionCredits_triggered();
    void on_actionAleitung_triggered();
    void on_actionSpeichern_triggered();
    void on_actionSchliessen_triggered();
    void on_actionRueckg_ngig_triggered();
    void on_action_oeffnen_von_triggered();
    void on_actionSpeichern_als_triggered();
    void on_actionEinstellungen_triggered();
    void on_actionWiederherstellen_triggered();
    void on_textEdit_textChanged();
    void on_textEdit_cursorPositionChanged();
    void on_fontComboBox_currentFontChanged(const QFont &f);
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_comboBox_2_currentTextChanged(const QString &arg1);
    void on_doubleSpinBox_valueChanged(double arg1);
    void on_actionHyperlink_triggered();
    void on_actionKopieren_triggered();
    void on_actionEinf_gen_triggered();
    void on_actionAusschneiden_triggered();
    void on_actionDruck_Vorschau_triggered();

private:
    Ui::MainWindow *ui;
    void loadsettings();
    void loadtheme();
    void loadicons();
    void loadDevMode();
    void closeEvent(QCloseEvent *event);
    void savecolor();
    void inittimer();
    void print();
    void highlightCurrentLine();

    Highlighter *highlighter;
    StandartHighlighter *standarthighlighter;
};

#endif // MAINWINDOW_H
