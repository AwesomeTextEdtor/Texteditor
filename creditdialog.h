#ifndef CREDITDIALOG_H
#define CREDITDIALOG_H

#include <QDialog>

namespace Ui {
class CreditDialog;
}

class CreditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreditDialog(QWidget *parent = 0);
    ~CreditDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::CreditDialog *ui;
};

#endif // CREDITDIALOG_H
