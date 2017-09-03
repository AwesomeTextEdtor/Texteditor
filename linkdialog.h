#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QDialog>

namespace Ui {
class linkDialog;
}

class linkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit linkDialog(QWidget *parent = 0);
    ~linkDialog();
    QString name,url,hyperlink;

private slots:
    void on_buttonBox_accepted();

private:
    Ui::linkDialog *ui;
};

#endif // LINKDIALOG_H
