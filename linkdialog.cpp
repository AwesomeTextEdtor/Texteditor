#include "linkdialog.h"
#include "ui_linkdialog.h"

LinkDialog::LinkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LinkDialog)
{
    ui->setupUi(this);
}

LinkDialog::~LinkDialog()
{
    delete ui;
}
void LinkDialog::on_buttonBox_accepted()
{
    url = ui->lineEdit->text();
    name = ui->lineEdit_2->text();
    hyperlink =  "<a href=\""+url+"\"><span style=\" text-decoration: underline; color:#007af4;\">"+name+"</span></a>";
    accept();
}

void LinkDialog::on_buttonBox_rejected()
{
    reject();
}










