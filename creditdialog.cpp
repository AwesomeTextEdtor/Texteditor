#define CREDITDIALOG
//#include "includes.h"

#include "creditdialog.h"
#include "ui_creditdialog.h"

CreditDialog::CreditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreditDialog)
{
    ui->setupUi(this);
    ui->label->setTextInteractionFlags(Qt::LinksAccessibleByMouse);
    ui->label->setOpenExternalLinks(true);
}

CreditDialog::~CreditDialog()
{
    delete ui;
}

void CreditDialog::on_pushButton_clicked()
{
    done(1);
}

#undef CREDITDIALOG
