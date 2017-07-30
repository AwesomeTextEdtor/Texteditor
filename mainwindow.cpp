#define  MAINWINDOW_CPP
//#include "includes.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createfiledialog.h"
#include "helpdialog.h"
#include "creditdialog.h"
#include "settingsdialog.h"
#include "qfont.h"
#include <limits.h>
#include <QFont>
#include <QString>
#include <QMenuBar>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QByteArray>
#include <QCloseEvent>
#include <QList>
#include <QColorDialog>
#include <QColor>
#include <QTranslator>
#include <QObject>
#include <QTimer>
#include <QTimerEvent>
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/QAbstractPrintDialog>

char out[127];
int i, autocomplete;
QString text, datei, pfad = "", name = "file.txt";
QString mylanguage, usage, savecolorchar, autosaveintervall, junk;
bool v_checked = 0, saved = 1, devmode=false;
QColor textcolor, initial = Qt::white, color, customcolor[16];
QColorDialog::ColorDialogOptions options;

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
        char* dataf = new char[text.length() + 1];
        char outs[2] = ";";
        strcpy(dataf, text.toLatin1().data());
        pfad = strtok(dataf, outs);
        mylanguage = strtok(NULL, outs);
        usage = strtok(NULL, outs);
        autosaveintervall = strtok(NULL, outs);
        junk = strtok(NULL, outs);
        junk = strtok(NULL, outs);
        autocomplete = junk.toInt();
        //other Settings    setting = strtok(NULL, outs);
        for(i= 0; i < 16; i++)
        {
            QString addColor = strtok(NULL, outs);
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
            autosaveintervall = "0.5 min";
        if(usage == "Entwicklung")
            loadDevMode();
        ui->label->setText(pfad);
        inittimer();

    }
    else
    {
        bool create = false;
        QFile c("tmp.txt");
        c.open(QIODevice::WriteOnly);
        c.write(tr("Die Einstellungsdatei existiert nicht\nSoll sie erstellt werden?").toLatin1().data());    c.close();
        CreateFileDialog a;
        create = a.exec();
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            SettingsDialog a;
            a.exec();
            fp =fp;
            goto settings;
        }
    }
    FILE* fp;
    fp = fopen("tmp.txt", "w");
    fclose(fp);
}

void MainWindow::loadicons()
{
    MainWindow::setWindowIcon(QIcon(":/Icons/icon.png"));
    ui->actionExportieren->setIcon(QIcon(":/Icons/export.png"));
    ui->actionSpeichern_als->setIcon(QIcon(":/Icons/save.png"));
    ui->actionSpeichern->setIcon(QIcon(":/Icons/save.png"));
    ui->actionOeffnen->setIcon(QIcon(":/Icons/open.png"));
    ui->actionDrucken->setIcon(QIcon(":/Icons/print.png"));
    ui->actionSchliessen->setIcon(QIcon(":/Icons/quit.png"));
    ui->actionRueckg_ngig->setIcon(QIcon(":/Icons/undo.png"));
    ui->actionWiederherstellen->setIcon(QIcon(":/Icons/redo.png"));
    ui->actionEinstellungen->setIcon(QIcon(":/Icons/settings.png"));
    ui->actionAleitung->setIcon(QIcon(":/Icons/icon.png"));
    ui->actionCredits->setIcon(QIcon(":/Icons/icon.png"));
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

void MainWindow::on_pushButton_4_clicked()      {
    if(!ui->checkBox_5->isChecked()) exportf(); else exportfv();}

void MainWindow::on_pushButton_3_clicked()
{
    QCloseEvent *e = NULL;
    closeEvent(e);
    remove("tmp.txt");
    qApp->quit();
}

void MainWindow::save()
{
    saved = true;
    QFile c("tmp.txt");
    c.open(QIODevice::WriteOnly);
    c.write(tr("Die Datei existiert nicht\nSoll sie erstellt werden?").toLatin1().data());    c.close();
    QFont Font = ui->textEdit->font();
    QString ending;
    //scan for ending
    if(ending == "gef")
        ;
    else{
        if(!ui->checkBox_5->isChecked())
            savef();
        else
            savefv();
    }
    ui->textEdit->setFont(Font);
}
void MainWindow::open()
{
    QFile c("tmp.txt");
    c.open(QIODevice::WriteOnly);
    c.write(tr("Die Datei existiert nicht\nSoll sie erstellt werden?").toLatin1().data());    c.close();
    QFont Font = ui->textEdit->font();
    QString ending;
    //scan for ending
    if(ending == "gef")
        ;
    else{
        if(!ui->checkBox_5->isChecked())
            openf();
        else
            openfv();
    }
    ui->textEdit->setFont(Font);
}

void MainWindow::openf()
{
    name = ui->lineEdit->text();
    pfad = ui->label->text();
    datei = pfad + name;
    QFile f(datei);
    QTextStream in(&f);
    openf:if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        ui->textEdit->setHtml(text);
    }
    else
    {
        bool create = false;
        QFile c("tmp.txt");
        c.open(QIODevice::WriteOnly);
        c.write(tr("Die Datei existiert nicht\nSoll sie erstellt werden?").toLatin1().data());    c.close();
        CreateFileDialog a;
        create = a.exec();;
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            fp =fp;
            goto openf;
        }
    }
}

void MainWindow::savef()
{
    name = ui->lineEdit->text();
    pfad = ui->label->text();
    datei = pfad + name;
    QFile f(datei);
    QTextStream in(&f);
    if(f.open(QIODevice::ReadOnly))
    {
        f.close();
        savef:if(f.open(QIODevice::WriteOnly))
        {
            text = ui->textEdit->toPlainText();
            char* dataf = new char[text.length() + 1];
            strcpy(dataf, text.toLatin1().data());
            if(v_checked == 1)
            {
                for(i = 0; i < (text.length()+1); i++)
                    dataf[i] = dataf[i]+10;
            }
            f.write(dataf, strlen(dataf));
        }
        else
        {
            bool create = false;
            QFile c("tmp.txt");
            c.open(QIODevice::WriteOnly);
            c.write(tr("Die Datei existiert nicht\nSoll sie erstellt werden?").toLatin1().data());    c.close();
            CreateFileDialog a;
            create = a.exec();
            if(create)
            {
                FILE* fp;
                char* file = new char[datei.length() + 1];
                strcpy(file, datei.toLatin1().data());
                fp = fopen(file, "w");
                fp =fp;
                goto savef;
            }
        }
    }
}

void MainWindow::exportf()
{
    name = ui->lineEdit->text();
    pfad = ui->label->text();
    datei = pfad + name;
    QFile f(datei);
    QTextStream in(&f);
    if(f.open(QIODevice::ReadOnly))
    {
        f.close();
        exportf:if(f.open(QIODevice::WriteOnly))
        {
            text = ui->textEdit->toHtml();
            char* dataf = new char[text.length() + 1];
            strcpy(dataf, text.toLatin1().data());
            if(v_checked == 1)
            {
                for(i = 0; i < (text.length()+1); i++)
                    dataf[i] = dataf[i];
            }
            f.write(dataf, strlen(dataf));
        }
        else
        {
            bool create = false;
            QFile c("tmp.txt");
            c.open(QIODevice::WriteOnly);
            c.write(tr("Die Datei existiert nicht\nSoll sie erstellt werden?").toLatin1().data());    c.close();
            CreateFileDialog a;
            create = a.exec();
            if(create)
            {
                FILE* fp;
                char* file = new char[datei.length() + 1];
                strcpy(file, datei.toLatin1().data());
                fp = fopen(file, "w");
                fp =fp;
                goto exportf;
            }
        }
    }
}


void MainWindow::openfv()
{
    for(i=0;i<127;i++)
    {
        out[i] = i+127;
    }
    name = ui->lineEdit->text();
    pfad = ui->label->text();
    datei = pfad + name;
    QFile f(datei);
    QTextStream in(&f);
    openfv:if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        char* textin = new char[text.length()+1];
        FILE* fp;
        char* file = new char[datei.length() + 1];
        strcpy(file, datei.toLatin1().data());
        fp = fopen(file, "r");
        fscanf(fp, "%s", textin);
        for(i = 0; i < (text.length()+1); i++)
        {
            textin[i] = textin[i] - 10;
        }
        text = strtok(textin, out);
        ui->textEdit->setHtml(text);
    }
    else
    {
        bool create = false;
        QFile c("tmp.txt");
        c.open(QIODevice::WriteOnly);
        c.write(tr("Die Datei existiert nicht\nSoll sie erstellt werden?").toLatin1().data());    c.close();
        CreateFileDialog a;
        create = a.exec();;
        if(create)
        {
            FILE* fp;
            char* file = new char[datei.length() + 1];
            strcpy(file, datei.toLatin1().data());
            fp = fopen(file, "w");
            fp = fp;
            goto openfv;
        }
        create = false;
    }
}

void MainWindow::savefv()
{
    name = ui->lineEdit->text();
    pfad = ui->label->text();
    datei = pfad + name;
    QFile f(datei);
    QTextStream in(&f);
    if(f.open(QIODevice::ReadOnly))
    {
        f.close();
        savefv:if(f.open(QIODevice::WriteOnly))
        {
            text = ui->textEdit->toPlainText();
            char* dataf = new char[text.length() + 1];
            strcpy(dataf, text.toLatin1().data());
                for(i = 0; i < (text.length()+1); i++)
                    dataf[i] = dataf[i]+10;
            f.write(dataf, strlen(dataf));
        }
        else
        {
            bool create = false;
            CreateFileDialog a;
            create = a.exec();
            if(create)
            {
                FILE* fp;
                char* file = new char[datei.length() + 1];
                strcpy(file, datei.toLatin1().data());
                fp = fopen(file, "w");
                fp = fp;
                goto savefv;
            }
            create = false;
        }
    }
}

void MainWindow::exportfv()
{
    name = ui->lineEdit->text();
    pfad = ui->label->text();
    datei = pfad + name;
    QFile f(datei);
    QTextStream in(&f);
    if(f.open(QIODevice::ReadOnly))
    {
        f.close();
        exportfv:if(f.open(QIODevice::WriteOnly))
        {
            text = ui->textEdit->toHtml();
            char* dataf = new char[text.length() + 1];
            strcpy(dataf, text.toLatin1().data());
                for(i = 0; i < (text.length()+1); i++)
                    dataf[i] = dataf[i];
            f.write(dataf, strlen(dataf));
        }
        else
        {
            bool create = false;
            QFile c("tmp.txt");
            c.open(QIODevice::WriteOnly);
            c.write(tr("Die Datei existiert nicht\nSoll sie erstellt werden?").toLatin1().data());    c.close();
            CreateFileDialog a;
            create = a.exec();
            if(create)
            {
                FILE* fp;
                char* file = new char[datei.length() + 1];
                strcpy(file, datei.toLatin1().data());
                fp = fopen(file, "w");
                fp = fp;
                goto exportfv;
            }
            create = false;
        }
    }
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
        QFont Font = ui->textEdit->font();
        text = ui->textEdit->toPlainText();
        if(text.at(ui->textEdit->textCursor().position()-1) == "(")
        {
            text.insert(ui->textEdit->textCursor().position(), ")");
            ui->textEdit->setText(text);
            cursor.setPosition(cursor.position()-1);
            ui->textEdit->setTextCursor(cursor);
        }
        else if(text.at(ui->textEdit->textCursor().position()-1) == "{")
        {
            text.insert(ui->textEdit->textCursor().position(), "}");
            ui->textEdit->setText(text);
            cursor.setPosition(cursor.position()-1);
            ui->textEdit->setTextCursor(cursor);
        }
        else if(text.at(ui->textEdit->textCursor().position()-1) == "[")
        {
            text.insert(ui->textEdit->textCursor().position(), "]");
            ui->textEdit->setText(text);
            cursor.setPosition(cursor.position()-1);
            ui->textEdit->setTextCursor(cursor);
        }
        else if(text.at(ui->textEdit->textCursor().position()-1) == "<")
        {
            text.insert(ui->textEdit->textCursor().position(), ">");
            ui->textEdit->setText(text);
            cursor.setPosition(cursor.position()-1);
            ui->textEdit->setTextCursor(cursor);
        }
        ui->textEdit->setFont(Font);
    }
//    if(devmode)
//        highlighter->setDocument(ui->textEdit->document());
}


void MainWindow::on_textEdit_cursorPositionChanged()
{
    if(usage == tr("Entwicklung").toLatin1().data())
        highlightCurrentLine();
}

void MainWindow::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!ui->textEdit->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor = QColor(Qt::darkGray).lighter(160);

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

void MainWindow::on_actionExportieren_triggered()
{
    if(!ui->checkBox_5->isChecked()) exportf(); else exportfv();
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

void MainWindow::on_actionSchliessen_triggered()
{
    QCloseEvent *e = NULL;
    closeEvent(e);
    remove("tmp.txt");
    qApp->quit();
}

void MainWindow::on_actionEinstellungen_triggered()
{
    SettingsDialog a;
    a.exec();
    loadsettings();
}

void MainWindow::on_actionRueckg_ngig_triggered()       {    ui->textEdit->undo();}

void MainWindow::on_actionWiederherstellen_triggered()  {    ui->textEdit->redo();}

void MainWindow::on_actionSpeichern_als_triggered()
{
    QFileDialog a;
    if(a.exec())
    {
        ui->label->setText(a.selectedFiles().last());
        ui->lineEdit->setText("");
    }
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
    QTextStream in(&f);
    if(f.open(QIODevice::ReadOnly))
    {
        text = in.readAll();
        f.close();
        if(f.open(QIODevice::WriteOnly))
        {
            char out[2] = ";";
            text = strtok(text.toLatin1().data(), out);
            text = text + ';' + strtok(NULL, out) + ';';
            text = text + strtok(NULL, out) + ';';
            text = text + strtok(NULL, out) + ';';
            text = text + strtok(NULL, out) + ';';
            text = text + strtok(NULL, out) + ';'; //dublicate when you add a new setting
            for(i = 0; i < 16; i++)
            {
                customcolor[i] = QColorDialog::customColor(i);
                savecolorchar = customcolor[i].name();
                text = text + savecolorchar + ';';
            }
            text = text+"_";
            char* dataf = new char[text.length() + 1];
            strcpy(dataf, text.toLatin1().data());
            f.write(dataf, strlen(dataf));
        }
    }
}

void MainWindow::closeEvent( QCloseEvent *event)
{
    if(!saved)
    {
        QFile c("tmp.txt");
        c.open(QIODevice::WriteOnly);
        c.write(tr("Es gibt ungespeicherte änderungen\nSoll alles gespeichert werden?").toLatin1().data());    c.close();
        CreateFileDialog a;
        if(a.exec() == 1)
            save();
    }
    savecolor();
    remove("tmp.txt");
    QFile tmp("tmp.txt");
    datei = "settings.txt";
    QFile f(datei);
    f.close();
    if(tmp.remove())
        event->accept();
}

#undef MAINWINDOW_CPP





