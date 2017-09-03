#include "tabledialog.h"
#include "ui_tabledialog.h"

tableDialog::tableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tableDialog)
{
    ui->setupUi(this);
}

tableDialog::~tableDialog()
{
    delete ui;
}

void tableDialog::on_spinBox_valueChanged(int arg1)
{
    columns = arg1;
}

void tableDialog::on_spinBox_2_valueChanged(int arg1)
{
    rows = arg1;
}
