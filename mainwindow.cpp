#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "deenscript.h"
#include "gefile.h"
#include "settingsdialog.h"
#include "tabledialog.h"
#include "linkdialog.h"
#include "creditdialog.h"
#include "helpdialog.h"
#include <QFile>
#include <QDebug>
#include <QTimer>
#include <QPrinter>
#include <QSettings>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QTranslator>
#include <QColorDialog>
#include <QPrintDialog>
#include <QStyleFactory>
#include <QSystemTrayIcon>
#include <QPrintPreviewDialog>
#include <QTextDocumentWriter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    settings = new QSettings("Galaxyqasar", "Texteditor",this);
    MyTranslator = new QTranslator(this);
    QtTranslator = new QTranslator(this);
    loadsettings();
    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon,SIGNAL(activated(QSystemTrayIcon::ActivationReason)),this,SLOT(showt()));
    connect(ui->textEdit,SIGNAL(customContextMenuRequested(const QPoint&)),this,SLOT(showContextMenu(const QPoint&)));
    ui->spinBoxTextSize->setValue(12.00);
    ui->textEdit->setContextMenuPolicy(Qt::CustomContextMenu);
    ui->textEdit->setUndoRedoEnabled(true);
    ui->textEdit->setFontPointSize(ui->spinBoxTextSize->value());
    standarthighlighter = new StandartHighlighter(ui->textEdit->document());
    options = QColorDialog::DontUseNativeDialog;
    loadCompilers();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete settings;
}

void MainWindow::loadsettings()
{
    ui->comboBoxQuickColorSelect->clear();
    settings->beginGroup("Mainwindow");
    ui->labelPath->setText(settings->value("path",tr("fehler")).toString());
    autocompleteb = settings->value("autocomplete", false).toBool();
    highlightCurrentL = settings->value("highlightCurrentLine", false).toBool();
    ui->comboBoxQuickColorSelect->addItems(settings->value("colors").toStringList());
    usage = settings->value("usage", tr("Büroarbeit")).toString();
    timeintervall = settings->value("autosave", tr("Nie")).toString();
    language = settings->value("language", "English").toString();
    settings->endGroup();
    if(autocompleteb)
        connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(autocomplete()));
    else if(!autocompleteb)
        disconnect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(autocomplete()));
    QPixmap pixmap(10,10);
    for(int i=0;i<16;i++){
        pixmap.fill(QColor(ui->comboBoxQuickColorSelect->itemText(i)));
        ui->comboBoxQuickColorSelect->setItemIcon(i, QIcon(pixmap));
    }
    if(usage == tr("Entwicklung"))
        loadDevMode();
    else if(usage == tr("Büroarbeit"))
        loadStdMode();
    else if(usage == tr("Wissenschaftlich"))
        loadScienceMode();
    if(!(timeintervall == tr("Nie")))
        inittimer();
}

void MainWindow::inittimer()
{
    QString string = timeintervall.split(" ", QString::KeepEmptyParts).first();
    int intervall = string.toDouble()*60*1000;
    QTimer *autosavetimer = new QTimer(this);
    autosavetimer->stop();
    connect(autosavetimer, SIGNAL(timeout()), this, SLOT(save()));
    autosavetimer->start(intervall);
}

void MainWindow::openFile(QString filename)
{
    ui->labelPath->setText(filename);
    open();
}

void MainWindow::loadDevMode()
{
    if(highlightCurrentL)
        highlightCurrentLine();
    else
        ui->textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
    devhighligter = new Highlighter(ui->textEdit->document());
    devmode = true;
    ui->tabWidget->addTab(ui->bashTab, tr("Bash"));
    ui->compilerComboBox->show();
    ui->executeButton->show();
}

void MainWindow::loadStdMode()
{
    devmode = false;
    ui->textEdit->setExtraSelections(QList<QTextEdit::ExtraSelection>());
    ui->tabWidget->removeTab(ui->tabWidget->indexOf(ui->bashTab));
    ui->compilerComboBox->hide();
    ui->executeButton->hide();
}

void MainWindow::loadScienceMode()
{
    ;
}

void MainWindow::loadCompilers(QString filename)
{
    if(filename == "Settings"){
        //load from Settings
    }
    else{
        //load from xml file
    }
}

void MainWindow::on_buttonBold_toggled(bool b_checked)
{
    if(b_checked)
        ui->textEdit->setFontWeight(QFont::Bold);
    else
        ui->textEdit->setFontWeight(QFont::Normal);
}

void MainWindow::on_buttonFixedOut_toggled(bool f_checked)
{
    QTextCharFormat font = ui->textEdit->textCursor().charFormat();
    font.setFontStrikeOut(f_checked);
    ui->textEdit->setCurrentCharFormat(font);
}

void MainWindow::on_comboBoxTextJustiefy_currentTextChanged(const QString &arg1)
{
    if(arg1 == tr("Linksbündig"))
        ui->textEdit->setAlignment(Qt::AlignLeft);
    else if(arg1 == tr("Zentriert"))
        ui->textEdit->setAlignment(Qt::AlignHCenter);
    else if(arg1 == tr("Rechtsbündig"))
        ui->textEdit->setAlignment(Qt::AlignRight);
    else if(arg1 == tr("Blocksatz"))
        ui->textEdit->setAlignment(Qt::AlignJustify);
}

void MainWindow::on_buttonSave_clicked()
{
    save();
}

void MainWindow::on_buttonOpen_clicked()
{
    open();
}

void MainWindow::on_buttonPrint_clicked()
{
    print();
}

void MainWindow::on_buttonTextColor_clicked()
{
    QStringList tmp;
    textcolor = QColorDialog::getColor(Qt::white, NULL, NULL, options);
    ui->textEdit->setTextColor(textcolor);
    ui->comboBoxQuickColorSelect->clear();
    for(int i= 0; i < 16; i++)
    {
        customcolor[i] = QColorDialog::customColor(i);
        QString addColor = customcolor[i].name();
        QColorDialog::setCustomColor(i, customcolor[i]);
        QPixmap pixmap(10, 10);
        pixmap.fill(customcolor[i]);
        QIcon colorIcon(pixmap);
        ui->comboBoxQuickColorSelect->addItem(colorIcon, addColor);
        tmp<<addColor;
    }
    settings->beginGroup("Mainwindow");
    settings->setValue("colors", tmp);
    settings->endGroup();
}

void MainWindow::on_actionOpen_triggered()
{
    open();
}

void MainWindow::on_actionOpenFrom_triggered()
{
    QFileDialog a;
    if(a.exec())
    {
        ui->labelPath->setText(a.selectedFiles().last());
    }
    open();
}

void MainWindow::on_actionSave_triggered()
{
    save();
}

void MainWindow::on_actionSaveAs_triggered()
{
    QFileDialog a;
    if(a.exec())
    {
        ui->labelPath->setText(a.selectedFiles().last());
    }
    save();
}

void MainWindow::on_actionPrint_triggered()
{
    print();
}

void MainWindow::on_actionPrintPreview_triggered()
{
    QPrinter printer(QPrinter::HighResolution);
    QPrintPreviewDialog preview(&printer, this);
    connect(&preview, &QPrintPreviewDialog::paintRequested, this, &MainWindow::printpreview);
    preview.exec();
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionSettings_triggered()
{
    SettingsDialog a;
    a.setSettings(settings, this);
    a.exec();
    loadsettings();
}

void MainWindow::on_actionImage_triggered()
{
    QFileDialog a;
    a.exec();
    ui->textEdit->textCursor().insertImage(QImage(a.selectedFiles().last()),\
                                           a.selectedFiles().last());
}

void MainWindow::on_actionTable_triggered()
{
    tableDialog a;
    a.exec();
    ui->textEdit->textCursor().insertTable(a.rows, a.columns);
}

void MainWindow::on_actionList_triggered()
{
    ui->textEdit->textCursor().insertList(QTextListFormat::ListDisc);
}

void MainWindow::on_actionHyperlink_triggered()
{
    linkDialog a;
    QString html;
    if(a.exec()){
        html = a.hyperlink;
        ui->textEdit->textCursor().insertHtml(html);}
}

void MainWindow::on_actionToggleFullscreen_triggered()
{
    if(!isFullScreen()){
        hide();
        showFullScreen();
    }
    else if(isFullScreen()){
        hide();
        showNormal();
    }
}

void MainWindow::on_actionHide_triggered()
{
    trayIcon->show();
    hide();
}

void MainWindow::on_actionHelp_triggered()
{
    HelpDialog *a;
    a = new HelpDialog(this);
    a->show();
}

void MainWindow::on_actionCredits_triggered()
{
    CreditDialog *a;
    a = new CreditDialog(this);
    a->show();
}

void MainWindow::on_actionReload_triggered()
{
    open();
}

void MainWindow::on_comboBoxQuickColorSelect_currentTextChanged(const QString &arg1)
{
    ui->textEdit->setTextColor(QColor(arg1));
}

void MainWindow::on_executeButton_clicked()
{
    if(ui->compilerComboBox->currentText() == "Qt Quick"){
        engine.loadData(ui->textEdit->toPlainText().toLatin1());
        if (engine.rootObjects().isEmpty())
            return;
    }
    else if(ui->compilerComboBox->currentText() == "GCC C"){
        save();
        QString compilerPath = "D:\\Downloads\\tcc-master\\win32\\tcc.exe", programmPath = "D:\\test.exe";
        QString command = "echo compiling... && " + compilerPath + " " + filename + " -o " + programmPath + " && echo execute && pause && " + programmPath + " && pause";
        qDebug()<<command;
        system(QString("echo compiling... && " + compilerPath + " " + filename + " -o " + programmPath).toLatin1().data());
    }

}

void MainWindow::showt()
{
    show();
    trayIcon->hide();
}

void MainWindow::autocomplete()
{
    if(ui->textEdit->toPlainText().size() != 0)
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
//        else if(ui->textEdit->toPlainText().at(cursor.position()-1) == "\'"){
//            ui->textEdit->textCursor().insertText("\'");
//            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
//            ui->textEdit->setTextCursor(cursor);}
//        else if(ui->textEdit->toPlainText().at(cursor.position()-1) == "\""){
//            ui->textEdit->textCursor().insertText("\"");
//            cursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, 1);
//            ui->textEdit->setTextCursor(cursor);}
    }
}

void MainWindow::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!ui->textEdit->isReadOnly()) {
        QTextEdit::ExtraSelection selection;

        QColor lineColor;/*
        lineColor = QColor(ui->textEdit->palette().color());*/
        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = ui->textEdit->textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }

    ui->textEdit->setExtraSelections(extraSelections);
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

void MainWindow::clear(){
    ui->textEdit->clear();
}

void MainWindow::printpreview(QPrinter *printer)
{
    ui->textEdit->print(printer);
}


void MainWindow::print()
{
    QString printtext = ui->textEdit->toPlainText();
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

void MainWindow::open()
{
    QFont Font = ui->textEdit->font();
    QString ending;
    ending = ui->lineEditFile->text().split(".", QString::KeepEmptyParts).last();
    ui->textEdit->setFont(Font);
    path = ui->labelPath->text();
    file = path;
    if(!ui->lineEditFile->text().isEmpty())
        file.append(ui->lineEditFile->text());
    QFile f(file);
    QTextStream in(&f);
    open:if(f.open(QIODevice::ReadOnly))
    {
        if(ending == "gef"){
            GeFile gef;
            gef.setenscript(in.readAll());
            ui->textEdit->setHtml(gef.getdescript());
        }
        else if(ending == "html"){
            ui->textEdit->setHtml(in.readAll());}
        else{
            text = in.readAll();
            if(ui->checkBoxDeEnScript->isChecked())
                text = descript(text, 10);
            ui->textEdit->setPlainText(text);}
        saved = true;
        qDebug() << "opened";
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

void MainWindow::save()
{
    QFont Font = ui->textEdit->font();
    QString ending;
    ending = ui->lineEditFile->text().split(".", QString::KeepEmptyParts).last();
    ui->textEdit->setFont(Font);
    path = ui->labelPath->text();
    if(!ui->lineEditFile->text().isEmpty()){
        filename = ui->lineEditFile->text();
        file = path + filename;
    } else file = path;
    QFile f(file);
    save:if(f.exists())
    {
        if(f.open(QIODevice::WriteOnly))
        {
            if(ending == "gef"){
                GeFile gef;
                gef.setdescript(ui->textEdit->toHtml());
                f.write(gef.getenscript().toLatin1());
            }
            else if(ending == "odt"){
                QTextDocumentWriter w(file);
                w.write(ui->textEdit->document());}
            else if(ending == "pdf"){
                QPrinter printer(QPrinter::PrinterResolution);
                printer.setOutputFormat(QPrinter::PdfFormat);
                printer.setPaperSize(QPrinter::A4);
                printer.setOutputFileName(file);
                QTextDocument doc;  doc.setHtml(ui->textEdit->toHtml());
                doc.setPageSize(printer.pageRect().size());
                doc.print(&printer);}
            else if(ending == "html"){
                text = ui->textEdit->toHtml();
                f.write(text.toLatin1());}
            else{
                text = ui->textEdit->toPlainText();
                if(ui->checkBoxDeEnScript->isChecked())
                    text = enscript(text, 10);
                f.write(text.toLatin1());}
            saved = true;
            qDebug() << "saved";
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
    event->accept();
}


