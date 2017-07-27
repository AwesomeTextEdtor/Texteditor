#ifndef INCLUDES_H
#define INCLUDES_H

#ifdef MAINWINDOW_CPP
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "createfiledialog.h"
#include "qfont.h"
#include <QFont>
#include <QString>
#include <QMenuBar>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QByteArray>
#include <limits.h>
#include "helpdialog.h"
#include "creditdialog.h"
#include "settingsdialog.h"
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
#endif

#ifdef SETTINGSDIALOG
#include "settingsdialog.h"
#include "ui_settingsdialog.h"
#include <QFile>
#include <QTextStream>
#include <QString>
#include <string>
#include "createfiledialog.h"
#include <QColorDialog>
#endif

#ifdef MAIN
#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#endif

#ifdef HELPDIALOG
#include "helpdialog.h"
#include "ui_helpdialog.h"
#endif

#ifdef CREDITDIALOG
#include "creditdialog.h"
#include "ui_creditdialog.h"
#endif

#ifdef CREATEFILEDIALOG
#include "createfiledialog.h"
#include "ui_createfiledialog.h"
#include <QFile>
#include <QTextStream>
#include <stdio.h>
#include <mainwindow.h>
#endif

#endif // INCLUDES_H
