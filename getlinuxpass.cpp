#include "getlinuxpass.h"
#include "ui_getlinuxpass.h"

getLinuxPass::getLinuxPass(QWidget *parent, QString *pass) :
    QDialog(parent),
    ui(new Ui::getLinuxPass)
{
    ui->setupUi(this);

    strPassword = pass ;

    on_passwordLineEdit_textChanged();
    ui->passwordLineEdit->setEchoMode(QLineEdit::Password) ;
}

getLinuxPass::~getLinuxPass()
{
    strPassword = NULL ;
    delete ui;

}

void getLinuxPass::on_cancelButton_clicked()
{
    ui->passwordLineEdit->clear();
    *strPassword = QString() ;
    this->close();
}

void getLinuxPass::on_okButton_clicked()
{
    *strPassword = ui->passwordLineEdit->text() ;

    this->close();
}

void getLinuxPass::on_passwordLineEdit_textChanged()
{
    ui->okButton->setEnabled(!ui->passwordLineEdit->text().isEmpty());
}
