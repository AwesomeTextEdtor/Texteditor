#define  MAINWINDOW_CPP
//#include "includes.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpdialog.h"
#include "creditdialog.h"
#include "settingsdialog.h"
#include "deenscript.h"
#include "tabledialog.h"
#include "linkdialog.h"
#include "gefile.h"
#include <limits.h>
#include <stdio.h>

#include <QFile>
#include <QFont>
#include <QIcon>
#include <QList>
#include <QColor>
#include <QDebug>
#include <QTimer>
#include <QObject>
#include <QString>
#include <QMenuBar>
#include <QByteArray>
#include <QTextCodec>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTimerEvent>
#include <QTranslator>
#include <QColorDialog>
#include <QTextDocument>
#include <QTextDocumentWriter>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QPrintPreviewDialog>
#include <QtPrintSupport/QAbstractPrintDialog>

char out[127];
int i, autocomplete;
QString text, datei, pfad = "", name = "file.txt", themem;
QString mylanguage, usage, savecolorchar, autosaveintervall, junk;
bool v_checked = false, saved = true, devmode = false;
QColor textcolor, initial = Qt::white, color, customcolor[16];
QColorDialog::ColorDialogOptions options;
QMenu *editContextMenu;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    loadsettings();
    loadicons();
    ui->doubleSpinBox->setValue(12);
    ui->textEdit->setFontPointSize(12);
    ui->textEdit->setUndoRedoEnabled(true);
    QList<QString> alignment;
    alignment <<tr("Linksbündig") <<tr("Zentriert") <<tr("Rechtsbündig");
    ui->comboBox->addItems(alignment);
    ui->lineEdit->setText("");
    ui->textEdit->setTabStopWidth(30);
    saved = true;
    standarthighlighter = new StandartHighlighter(ui->textEdit->document());
    connect(ui->textEdit,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(showContextMenu(const QPoint&)));
    connect(ui->lineEdit,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(showContextMenu(const QPoint&)));
    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadsettings()
{
    datei = "settings.txt";
    QFile f(datei);
    QTextStream in(&f);
    settings:if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        QList<QString> settings = text.split(";", QString::KeepEmptyParts, Qt::CaseInsensitive);
        pfad = settings.first();
        mylanguage = settings.at(1);
        usage = settings.at(2);
        autosaveintervall = settings.at(3);
        themem = settings.at(4);
        autocomplete = settings.at(5).toInt();
        //other Settings    setting = strtok(NULL, outs);
        for(i= 0; i < 16; i++)
        {
            QString addColor = settings.at(i+6);
            customcolor[i] = addColor;
            QColorDialog::setCustomColor(i, customcolor[i]);
            QPixmap pixmap(10, 10);
            pixmap.fill(customcolor[i]);
            QIcon colorIcon(pixmap);
            ui->comboBox_2->addItem(colorIcon, addColor);
        }
        if(pfad == "")
            pfad = "C:\\";
        if(autosaveintervall == "")
            autosaveintervall = tr("Nie");
        if(usage == "Entwicklung")
            loadDevMode();
        ui->label->setText(pfad);
        inittimer();

    }
    else
    {
        QMessageBox messageBox;
        messageBox.addButton(QMessageBox::Yes);messageBox.addButton(QMessageBox::No);
        messageBox.setText(tr("Die Einstellungsdatei existiert nicht\nSoll sie erstellt werden?"));
        if(messageBox.exec() == QMessageBox::Yes)
        {
            f.open(QIODevice::ReadWrite);f.close();
            goto settings;
        }
    }
}

void MainWindow::loadicons()
{
    MainWindow::setWindowIcon(QIcon(":/Icons/icon.png"));
    ui->actionSpeichern_als->setIcon(QIcon(":/Icons/save.png"));
    ui->actionSpeichern->setIcon(QIcon(":/Icons/save.png"));
    ui->actionOeffnen->setIcon(QIcon(":/Icons/open.png"));
    ui->action_oeffnen_von->setIcon(QIcon(":/Icons/open.png"));
    ui->actionDrucken->setIcon(QIcon(":/Icons/print.png"));
    ui->actionSchliessen->setIcon(QIcon(":/Icons/quit.png"));
    ui->actionRueckg_ngig->setIcon(QIcon(":/Icons/undo.png"));
    ui->actionWiederherstellen->setIcon(QIcon(":/Icons/redo.png"));
    ui->actionEinstellungen->setIcon(QIcon(":/Icons/settings.png"));
    ui->actionAleitung->setIcon(QIcon(":/Icons/icon.png"));
    ui->actionCredits->setIcon(QIcon(":/Icons/icon.png"));
    ui->actionKopieren->setIcon(QIcon(":/Icons/copy.png"));
    ui->actionEinf_gen->setIcon(QIcon(":/Icons/paste.png"));
    ui->menuEinf_gen->setIcon(QIcon(":/Icons/paste (1).png"));
    ui->actionAusschneiden->setIcon(QIcon(":/Icons/scissors.png"));
}

void MainWindow::loadDevMode()
{
    highlightCurrentLine();
    highlighter = new Highlighter(ui->textEdit->document());
    devmode = true;
}

void MainWindow::inittimer()
{
    if(autosaveintervall == tr("Nie"))
        ;
    else
    {
        char* autosave = new char[autosaveintervall.length() + 1];
        strcpy(autosave, autosaveintervall.toLatin1().data());
        double intervall;
        char outs[2] = " ";
        QString string;
        string = strtok(autosave, outs);
        intervall = string.toDouble()*60*1000;
        i = intervall;
        QTimer *autosavetimer = new QTimer(this);
        autosavetimer->stop();
        connect(autosavetimer, SIGNAL(timeout()), this, SLOT(save()));
        autosavetimer->start(i);
    }
}

void MainWindow::showContextMenu(const QPoint &pt)
{
    QAction *clear;
    QMenu *menu = ui->textEdit->createStandardContextMenu();
    QList<QAction*> actions = menu->actions();
    clear = new QAction(QIcon(":/Icons/clear.png"), "Clear", this);
    connect(clear, &QAction::triggered, this, &MainWindow::clear);
    actions.at(0)->setIcon(QIcon(":/Icons/undo.png"));
    actions.at(1)->setIcon(QIcon(":/Icons/redo.png"));
    actions.at(3)->setIcon(QIcon(":/Icons/scissors.png"));
    actions.at(4)->setIcon(QIcon(":/Icons/copy.png"));
    actions.at(5)->setIcon(QIcon(":/Icons/copy.png"));
    actions.at(6)->setIcon(QIcon(":/Icons/paste.png"));
    actions.at(7)->setIcon(QIcon(":/Icons/delete.png"));
    actions.append(clear);
    for(int i=0;i<actions.size();i++)
        menu->addAction(actions.at(i));
    menu->exec(ui->textEdit->mapToGlobal(pt));
    delete menu;
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
    save();}

void MainWindow::on_pushButton_2_clicked()      {
    open();}

void MainWindow::save()
{
    QFont Font = ui->textEdit->font();
    QString ending;
    ending = ui->lineEdit->text().split(".", QString::KeepEmptyParts).last();
    ui->textEdit->setFont(Font);
    name = ui->lineEdit->text();
    pfad = ui->label->text();
    datei = pfad + name;
    QFile f(datei);
    save:if(f.open(QIODevice::ReadOnly))
    {   f.close();
        if(f.open(QIODevice::WriteOnly))
        {
            if(ending == "gef"){
                GeFile gef;
                gef.setdescript(ui->textEdit->toHtml());
                f.write(gef.getenscript().toLatin1());
            }
            else if(ending == "odt"){
                QTextDocumentWriter w(datei);
                w.write(ui->textEdit->document());}
            else if(ending == "pdf"){
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(datei);
                QTextDocument doc;  doc.setHtml(ui->textEdit->toHtml());
                doc.setPageSize(printer.pageRect().size());
                doc.print(&printer);}
            else if(ending == "html"){
                text = ui->textEdit->toHtml();
                f.write(text.toLatin1());}
            else{
                text = ui->textEdit->toPlainText();
                if(ui->checkBox_5->isChecked())
                    text = enscript(text, 10);
                f.write(text.toLatin1());}
            saved = true;
        }
    }
    else
    {
        QMessageBox messageBox;
        messageBox.addButton(QMessageBox::Yes);messageBox.addButton(QMessageBox::No);
        messageBox.setText(tr("Die Datei existiert nicht\nSoll sie erstellt werden?"));
        int ret = messageBox.exec();
        if(ret == QMessageBox::Yes)
        {
            f.open(QIODevice::ReadWrite);f.close();
            goto save;
        }
    }
}
void MainWindow::open()
{
    QFont Font = ui->textEdit->font();
    QString ending;
    ending = ui->lineEdit->text().split(".", QString::KeepEmptyParts).last();
    ui->textEdit->setFont(Font);
    name = ui->lineEdit->text();
    pfad = ui->label->text();
    datei = pfad + name;
    QFile f(datei);
    QTextStream in(&f);
    open:if(f.open(QIODevice::ReadOnly))
    {
        if(ending == "gef"){
            GeFile gef;
            text = in.readAll();
            gef.setenscript(text);
            ui->textEdit->setHtml(gef.getdescript());
        }
        else if(ending == "html"){
            text = in.readAll();
            ui->textEdit->setHtml(text);}
        else{
            text = in.readAll();
            if(ui->checkBox_5->isChecked())
                text = descript(text, 10);
            ui->textEdit->setPlainText(text);}
        saved = true;
    }
    else
    {
        QMessageBox messageBox;
        messageBox.addButton(QMessageBox::Yes);messageBox.addButton(QMessageBox::No);
        messageBox.setText(tr("Die Datei existiert nicht\nSoll sie erstellt werden?"));
        if(messageBox.exec() == QMessageBox::Yes)
        {
            f.open(QIODevice::ReadWrite);f.close();
            goto open;
        }
    }
}

void MainWindow::clear()
{
    ui->textEdit->clear();
}

void MainWindow::printpreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}

void MainWindow::print()
{
    QString printtext = ui->textEdit->toPlainText();
    QFont font = ui->textEdit->font();
    QTextDocument document(printtext, this);
    QPrinter printer;
    printer.setResolution(QPrinter::HighResolution);
    QPrintDialog PrintDialog(&printer);
    if(PrintDialog.exec() == QDialog::Accepted)
    {
        document.setHtml(ui->textEdit->toHtml());
        document.print(&printer);
    }
}

void MainWindow::on_textEdit_textChanged()
{
    saved = false;
    if(autocomplete && ui->textEdit->toPlainText().size() != 0)
    {
        QTextCursor cursor= ui->textEdit->textCursor();
        if(ui->textEdit->toPlainText().at(cursor.position()-1) == "("){
            ui->textEdit->textCursor().insertText(")");
            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
            ui->textEdit->setTextCursor(cursor);}
        else if(ui->textEdit->toPlainText().at(cursor.position()-1) == "{"){
            ui->textEdit->textCursor().insertText("}");
            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
            ui->textEdit->setTextCursor(cursor);}
        else if(ui->textEdit->toPlainText().at(cursor.position()-1) == "["){
            ui->textEdit->textCursor().insertText("]");
            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
            ui->textEdit->setTextCursor(cursor);}
        else if(ui->textEdit->toPlainText().at(cursor.position()-1) == "<"){
            ui->textEdit->textCursor().insertText(">");
            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
            ui->textEdit->setTextCursor(cursor);}
    }
}

void MainWindow::on_textEdit_cursorPositionChanged()
{
    if(usage == tr("Entwicklung").toLatin1().data())
        highlightCurrentLine();
//    ui->checkBox->setChecked(ui->textEdit->currentFont().bold());         Buggy
//    ui->checkBox_2->setChecked(ui->textEdit->currentFont().italic());
//    ui->checkBox_2->setChecked(ui->textEdit->currentFont().underline());
//    ui->doubleSpinBox->setValue(ui->textEdit->currentFont().pointSize());
}

void MainWindow::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!ui->textEdit->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor;
        if(themem == "Normal")
            lineColor = QColor(Qt::darkGray).lighter(160);
        else
            lineColor = QColor(Qt::darkGray).lighter(50);
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = ui->textEdit->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    ui->textEdit->setExtraSelections(extraSelections);
}

void MainWindow::on_actionOeffnen_triggered()
{
    open();
}

void MainWindow::on_actionSpeichern_triggered()
{
     save();
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

void MainWindow::on_actionDruck_Vorschau_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &MainWindow::printpreview);
    preview.exec();
}

void MainWindow::on_actionSchliessen_triggered()
{
    close();
}

void MainWindow::on_actionEinstellungen_triggered()
{
    SettingsDialog a;
    a.exec();
    loadsettings();
}

void MainWindow::on_actionKopieren_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionEinf_gen_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionAusschneiden_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionBild_triggered()
{
    QFileDialog a;
    a.exec();
    ui->textEdit->textCursor().insertImage(QImage(a.selectedFiles().last()),\
                                           a.selectedFiles().last());
}

void MainWindow::on_actionTabelle_triggered()
{
    TableDialog a;
    if(a.exec())
        ui->textEdit->textCursor().insertTable(a.rows, a.columns);
}

void MainWindow::on_actionHyperlink_triggered()
{
    LinkDialog a;
    QString html;
    if(a.exec()){
        html = a.hyperlink;
        ui->textEdit->textCursor().insertHtml(html);}
}

void MainWindow::on_actionListe_triggered()
{
    ui->textEdit->textCursor().insertList(QTextListFormat::ListDisc);
}

void MainWindow::on_actionRueckg_ngig_triggered()       {    ui->textEdit->undo();}

void MainWindow::on_actionWiederherstellen_triggered()  {    ui->textEdit->redo();}

void MainWindow::on_actionSpeichern_als_triggered()
{
    QFileDialog a;
    if(a.exec())
    {
        QList<QString> tmpl = a.selectedFiles().last().split("/", QString::KeepEmptyParts);
        QString tmps;   tmpl.removeFirst();
        for(int i=0;i<tmpl.size()-1;i++)
            tmps.append("/"+tmpl.at(i));
        ui->label->setText(tmps+"/");
        ui->lineEdit->setText(a.selectedFiles().last().split("/", QString::KeepEmptyParts).last());
    }
    save();
}

void MainWindow::on_action_oeffnen_von_triggered()
{
    QFileDialog a;
    if(a.exec())
    {
        QList<QString> tmpl = a.selectedFiles().last().split("/", QString::KeepEmptyParts);
        QString tmps;   tmpl.removeFirst();
        for(int i=0;i<tmpl.size()-1;i++)
            tmps.append("/"+tmpl.at(i));
        ui->label->setText(tmps+"/");
        ui->lineEdit->setText(a.selectedFiles().last().split("/", QString::KeepEmptyParts).last());
    }
    open();
}

void MainWindow::on_actionDrucken_triggered()
{
    print();
}

void MainWindow::on_pushButton_6_clicked()
{
    print();
}

void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == tr("Linksbündig"))
        ui->textEdit->setAlignment(Qt::AlignLeft);
    else if(arg1 == tr("Zentriert"))
        ui->textEdit->setAlignment(Qt::AlignHCenter);
    else if(arg1 == tr("Rechtsbündig"))
        ui->textEdit->setAlignment(Qt::AlignRight);
}

void MainWindow::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    QColor textcolor = arg1;
    ui->textEdit->setTextColor(textcolor);
}

void MainWindow::on_pushButton_5_clicked()
{
    options = QColorDialog::DontUseNativeDialog;
    textcolor = QColorDialog::getColor(Qt::white, NULL, NULL, options);
    ui->textEdit->setTextColor(textcolor);
    ui->comboBox_2->clear();
    for(i= 0; i < 16; i++)
    {
        customcolor[i] = QColorDialog::customColor(i);
        QString addColor = customcolor[i].name();
        QColorDialog::setCustomColor(i, customcolor[i]);
        QPixmap pixmap(10, 10);
        pixmap.fill(customcolor[i]);
        QIcon colorIcon(pixmap);
        ui->comboBox_2->addItem(colorIcon, addColor);
    }
}

void MainWindow::savecolor()
{
    QFile f("settings.txt");
    if(f.open(QIODevice::ReadOnly))
    {
        f.close();
        if(f.open(QIODevice::WriteOnly))
        {
            text = pfad+";"+mylanguage+";"+usage+";"+\
                    autosaveintervall+";"+themem+";"+\
                    QString::number(autocomplete)+";";//+setting+";"
            for(i = 0; i < 16; i++)
            {
                customcolor[i] = QColorDialog::customColor(i);
                savecolorchar = customcolor[i].name();
                text = text + savecolorchar + ';';
            }
            text = text+"_";
            f.write(text.toLatin1());
        }
    }
}

void MainWindow::closeEvent( QCloseEvent *event)
{
    if(!saved)
    {
        QMessageBox messageBox;
        messageBox.addButton(QMessageBox::Yes);messageBox.addButton(QMessageBox::No);messageBox.addButton(QMessageBox::Cancel);
        messageBox.setText(tr("Es gibt ungespeicherte änderungen\nSoll alles gespeichert werden?"));
        int ret = messageBox.exec();
        if(ret == QMessageBox::Yes)
            save();
        else if(ret == QMessageBox::Cancel){
            event->ignore(); return;}
    }
    savecolor();
    datei = "settings.txt";
    QFile f(datei);
    f.close();
    event->accept();
}



#undef MAINWINDOW_CPP






















