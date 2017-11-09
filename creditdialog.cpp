#include "creditdialog.h"
#include "ui_creditdialog.h"

CreditDialog::CreditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditDialog)
{
    ui->setupUi(this);
}

CreditDialog::~CreditDialog()
{
    delete ui;
}
