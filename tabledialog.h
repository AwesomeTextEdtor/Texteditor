#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H

#include <QDialog>

namespace Ui {
class tableDialog;
}

class tableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit tableDialog(QWidget *parent = 0);
    ~tableDialog();
    int rows,columns;

private slots:
    void on_spinBox_valueChanged(int arg1);

    void on_spinBox_2_valueChanged(int arg1);

private:
    Ui::tableDialog *ui;
};

#endif // TABLEDIALOG_H
