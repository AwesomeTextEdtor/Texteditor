#include "linkdialog.h"
#include "ui_linkdialog.h"

linkDialog::linkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::linkDialog)
{
    ui->setupUi(this);
}

linkDialog::~linkDialog()
{
    delete ui;
}

void linkDialog::on_buttonBox_accepted()
{
    url = ui->lineEditUrl->text();
    name = ui->lineEditName->text();
    hyperlink =  "<a href=\""+url+"\"><span style=\" text-decoration: underline; color:#007af4;\">"+name+"</span></a>";
    accept();
}
