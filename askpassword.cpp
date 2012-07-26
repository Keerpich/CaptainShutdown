#include "askpassword.h"
#include "ui_askpassword.h"

AskPassword::AskPassword(QWidget *parent, QString pass) :
    QDialog(parent),
    ui(new Ui::AskPassword),
    strPassword (pass)
{
    ui->setupUi(this);

    ui->lineEdit->setEchoMode(QLineEdit::Password);

    connect (this, SIGNAL (accepted()), parent, SLOT(slAskAccepted())) ;
    connect (this, SIGNAL (rejected()), parent, SLOT (slAskRejected())) ;
}

AskPassword::~AskPassword()
{
    delete ui;
}

void AskPassword::on_cancelButton_clicked()
{
    ui->lineEdit->clear();

    reject() ;
}

void AskPassword::on_okButton_clicked()
{
    if (ui->lineEdit->text() == strPassword)
    {
        accept() ;
    }
    else
    {
        QMessageBox::critical (this, tr("Error"),
                               tr("Password doesn't match"), QMessageBox::Ok) ;
        ui->lineEdit->clear();
    }
}

void AskPassword::on_lineEdit_textChanged()
{
    ui->okButton->setEnabled(!ui->lineEdit->text().isEmpty());
}
