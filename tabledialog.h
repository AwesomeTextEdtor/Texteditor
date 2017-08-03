#ifndef TABLEDIALOG_H
#define TABLEDIALOG_H

#include <QDialog>

namespace Ui {
class TableDialog;
}

class TableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TableDialog(QWidget *parent = 0);
    ~TableDialog();
    int rows, columns;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_rows_valueChanged(int arg1);

    void on_columns_valueChanged(int arg1);

private:
    Ui::TableDialog *ui;
};



#endif // TABLEDIALOG_H












