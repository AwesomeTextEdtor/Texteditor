#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "syntaxhighlighter.h"
#include <QSettings>
#include <QMainWindow>
#include <QTranslator>
#include <QColorDialog>
#include <QSystemTrayIcon>
#include <QTextDocumentWriter>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void changeEvent(QEvent);

private slots:
    void on_buttonBold_toggled(bool b_checked);
    void on_buttonFixedOut_toggled(bool f_checked);
    void on_comboBoxTextJustiefy_currentTextChanged(const QString &arg1);
    void on_buttonSave_clicked();
    void on_buttonOpen_clicked();
    void on_buttonPrint_clicked();
    void on_buttonTextColor_clicked();
    void on_actionOpen_triggered();
    void on_actionOpenFrom_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionPrint_triggered();
    void on_actionPrintPreview_triggered();
    void on_actionClose_triggered();
    void on_actionUndo_triggered();
    void on_actionRedo_triggered();
    void on_actionCopy_triggered();
    void on_actionPaste_triggered();
    void on_actionCut_triggered();
    void on_actionSettings_triggered();
    void on_actionImage_triggered();
    void on_actionTable_triggered();
    void on_actionList_triggered();
    void on_actionHyperlink_triggered();
    void on_actionToggleFullscreen_triggered();
    void on_actionHide_triggered();
    void on_actionHelp_triggered();
    void on_actionCredits_triggered();
    void on_actionReload_triggered();
    void on_comboBoxQuickColorSelect_currentTextChanged(const QString &arg1);
    void save();
    void open();
    void clear();
    void print();
    void showt();
    void inittimer();
    void loadDevMode();
    void autocomplete();
    void loadsettings();
    void printpreview(QPrinter *printer);
    void showContextMenu(const QPoint &pt);
    void highlightCurrentLine();


private:
    void closeEvent(QCloseEvent *event);

    Ui::MainWindow *ui;
    Highlighter *devhighligter;
    StandartHighlighter *standarthighlighter;
    bool saved, autocompleteb, devmode;
    QSettings *settings;
    QString filename, file, text, path, language, usage, timeintervall;
    QColor textcolor, initial = Qt::white, color, customcolor[16];
    QColorDialog::ColorDialogOptions options;
    QSystemTrayIcon *trayIcon;
    QTranslator *MyTranslator, *QtTranslator;
};

#endif // MAINWINDOW_H
