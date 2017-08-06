#include "tabledialog.h"
#include "ui_tabledialog.h"

TableDialog::TableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TableDialog)
{
    ui->setupUi(this);
}

TableDialog::~TableDialog()
{
    delete ui;
}

void TableDialog::on_buttonBox_accepted()
{
    accept();
}

void TableDialog::on_buttonBox_rejected()
{
    reject();
}

void TableDialog::on_rows_valueChanged(int arg1)
{
    rows = arg1;
}

void TableDialog::on_columns_valueChanged(int arg1)
{
    columns = arg1;
}
