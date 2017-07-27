#ifndef CREATEFILEDIALOG_H
#define CREATEFILEDIALOG_H

#include <QDialog>

namespace Ui {
class CreateFileDialog;
}

class CreateFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateFileDialog(QWidget *parent = 0);
    ~CreateFileDialog();
    void setlabel();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::CreateFileDialog *ui;

};

#endif // CREATEFILEDIALOG_H
