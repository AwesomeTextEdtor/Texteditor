#ifndef LINKDIALOG_H
#define LINKDIALOG_H

#include <QDialog>

namespace Ui {
class LinkDialog;
}

class LinkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LinkDialog(QWidget *parent = 0);
    ~LinkDialog();
    QString url, name, hyperlink;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::LinkDialog *ui;
};

#endif // LINKDIALOG_H
